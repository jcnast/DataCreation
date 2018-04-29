#include "DataExport/CustomData/Headers/DataCreation.h"

#include "Core/Debugging/Headers/Macros.h"

#include "Core/Headers/Hash.h"
#include "Core/IO/Headers/IOUtils.h"

#include "DataExport/Headers/ExportException.h"

#include "DataExport/CustomData/Headers/DataExportUtils.h"

using namespace std::string_literals;

namespace Data
{
	namespace DataExport
	{
		void ExportCustomData(Ptr<SQLInstance> db, Ptr<File> directAssets)
		{
			LOG("Starting to export custom data");

			File customAssets(FilePath{ GetCWD() + "Resources/ExportedAssets/", "CustomAssets.h" }, ios::out);
			customAssets.Open();
			InitializeCustomAssetFile(&customAssets);

			Function<bool, Ptr<void>, List<String>, List<String>> forEachType = [db, &customAssets, directAssets](void* forwardedInfo, List<String> columnValues, List<String> columnNames)
			{
				// due to query, there will only ever be one column value (the table name)
				ExportDataTypeInformation(db, columnValues[0], &customAssets, directAssets);

				return false;
			};

			String allTypeQuery = "SELECT name FROM sqlite_master WHERE type='table'";

			ExportDirectReference_Open("CustomAssets", directAssets);
			if (!db->Query(allTypeQuery, forEachType, nullptr))
			{
				throw CustomExportException("Query to get tables failed");
			}
			ExportDirectReference_Close("CustomAssets", directAssets);

			FinalizeCustomAssetFile(&customAssets);

			LOG("Finished exporting custom data");
		}

		void ExportDataTypeInformation(Ptr<SQLInstance> db, String type, Ptr<File> customAssets, Ptr<File> directAssets)
		{
			LOG("Starting to export data type: " + type);

			Function<bool, Ptr<void>, List<String>, List<String>> formatConstruction = [db, type, customAssets, directAssets](void* forwardedInfo, List<String> columnValues, List<String> columnNames)
			{
				// due to query, there will only even be one column value (the sql statement)
				auto type = ExportDataType(columnValues[0], customAssets);
				ExportDataForType(db, move(type), directAssets);

				return false;
			};

			String typeFormatQuery = "Select sql from sqlite_master WHERE name = '" + type + "'";
			if (!db->Query(typeFormatQuery, formatConstruction, nullptr))
			{
				throw CustomExportException("Query to get format failed");
			}

			LOG("Finished exporting data type: " + type);
		}

		UniquePtr<DataType> ExportDataType(String sql, Ptr<File> customAssets)
		{
			LOG("Starting to export data type: " + sql);

			auto dataType = CreateType(sql);

			customAssets->CreateNewLine();
			customAssets->Write("// " + dataType->Name);
			customAssets->CreateNewLine();
			customAssets->Write(dataType->GetDefinition());
			customAssets->CreateNewLine();
			customAssets->Write(dataType->GetMetaTypeDefinition());
			customAssets->CreateNewLine();

			return dataType;

			LOG("Finished exporting data type: " + sql);
		}

		void ExportDataForType(Ptr<SQLInstance> db, UniquePtr<DataType> type, Ptr<File> directAssets)
		{
			LOG("Starting to export data with type: " + type->Name);

			FilePath exportTo = { GetCWD() + "Resources/ExportedAssets/CustomData/", "" };

			Function<bool, Ptr<void>, List<String>, List<String>> exportData = [dataType = type.get(), directAssets, exportTo](void* forwardedInfo, List<String> columnValues, List<String> columnNames)
			{
				MetaAssetData assetData;
				assetData.typeName = dataType->Name;
				assetData.typeAcronym = dataType->Acronym;

				String assetName;

				for (auto& prop : dataType->Properties)
				{
					if (prop != nullptr && prop->IsPrimaryKey)
					{
						assetName = prop->Name;
						break;
					}
				}

				auto IsReference = [dataType](String variableName)
				{
					if (variableName == "ExportDirectly")
					{
						LOG("Variable is 'ExportDirectly' - so is ignored");
						return false;
					}

					for (auto& prop : dataType->Properties)
					{
						if (prop != nullptr)
						{
							if (prop->Name == variableName)
							{
								auto line = prop->GetLine();
								return (line.find("AssetType<") < line.size());
							}
						}
					}

					return false;
				};

				for (uint i = 0; i < columnNames.size(); i++)
				{
					if (columnNames[i] == "ExportDirectly")
					{
						assetData.directExport = true;
						continue;
					}

					if (columnNames[i] == assetName)
					{
						assetData.assetName = columnValues[i];
					}

					MetaAssetDataProperty newVariable;
					newVariable.IsReference = IsReference(columnNames[i]);
					newVariable.variableName = columnNames[i];
					newVariable.variableValue = columnValues[i];

					Push(assetData.variables, newVariable);
				}

				ExportDataItemForType(assetData, exportTo, directAssets);

				return false;
			};

			String elementQuery = "Select * from " + type->Name;

			ExportDirectReference_Open(type->Name, directAssets);
			if (!db->Query(elementQuery, exportData, nullptr))
			{
				throw CustomExportException("Query to get assets failed");
			}
			ExportDirectReference_Close(type->Name, directAssets);

			LOG("Finished exporting data with type: " + type->Name);
		}

		void ExportDirectReference_Open(String name, Ptr<File> directAssets)
		{
			directAssets->Write("\t\tstruct " + name);
			directAssets->CreateNewLine();
			directAssets->Write("\t\t{");
			directAssets->CreateNewLine();
		}

		void ExportDirectReference_Close(String name, Ptr<File> directAssets)
		{
			auto acronym = Acronym(name);

			directAssets->Write("\t\t};");
			directAssets->CreateNewLine();
			directAssets->Write("\t\tconst " + name + " " + acronym + ";");
			directAssets->CreateNewLine();
		}

		void ExportDataItemForType(MetaAssetData asset, FilePath exportTo, Ptr<File> directAssets)
		{
			exportTo.File = ToString(HashValue(asset.assetName).H) + "." + asset.typeAcronym;
			LOG(exportTo.GetFullPath());
			File assetFile = File(exportTo, ios::out);
			assetFile.Open();
			assetFile.Clear();

			for (auto& variable : asset.variables)
			{
				auto value = (variable.IsReference ? ToString(HashValue(variable.variableValue).H) : variable.variableValue);
				assetFile.Write(variable.variableName + " " + value);
				assetFile.CreateNewLine();
			}

			if (asset.directExport)
			{
				directAssets->Write("\t\t\tconst AssetName<" + asset.typeName + "> " + asset.assetName + " = " + ToString(HashValue(asset.assetName).H) + ";");
				directAssets->CreateNewLine();
			}

			assetFile.Close();
		}

		void InitializeCustomAssetFile(Ptr<File> customAssets)
		{
			customAssets->Clear();

			String header = R"(
#pragma once

#include "Data/Headers/AssetType.h"

/*
This file is auto-generated.

DO NOT MODIFY
*/

namespace Data
{
)";
			customAssets->Write(header);
		}

		void FinalizeCustomAssetFile(Ptr<File> customAssets)
		{
			String footer = R"(
}
)";
			customAssets->Write(footer);
		}
	}
}