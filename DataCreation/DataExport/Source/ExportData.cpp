#include "DataExport/Headers/ExportData.h"

#include "Core/Debugging/Headers/Macros.h"
#include "Core/IO/Headers/IOUtils.h"

#include "DataExport/CustomData/Headers/DataCreation.h"

namespace Data
{
	namespace DataExport
	{
		void ExportData()
		{
			LOG("Starting to export data");
			auto directPath = FilePath{ GetCWD() + "Resources/ExportedAssets/", String("Assets.h") };
			auto directAssets = File(directPath, ios::out);
			directAssets.Clear();
			directAssets.Open();

			InitializeAssetsFile(&directAssets);

			ExportCustomData(&directAssets);
			ExportRenderingData(&directAssets);

			FinalizeAssetsFile(&directAssets);

			directAssets.Close();
			LOG("Finished exporting data");
		}

		void ExportCustomData(Ptr<File> directAssets)
		{
			LOG("Starting to export custom data");
			auto dbPath = FilePath{ GetCWD() + "Resources/ImportedAssets/CustomData/", String("Data.db") };
			SQLInstance db = SQLInstance(dbPath);
			db.Open();

			ExportCustomData(&db, directAssets);

			db.Close();
			LOG("Finished exporting custom data");
		}

		void ExportRenderingData(Ptr<File> directAssets)
		{
			LOG("Starting to export rendering data");



			LOG("Finished exporting rendering data");
		}

		void InitializeAssetsFile(Ptr<File> directAssets)
		{
			directAssets->Write(R"(
								#pragma once

								#include "Data/Headers/AssetType.h"
								#include "Data/Headers/AssetName.h"

								#include "CustomAssets.h"
								#include "MaterialAssets.h"
								#include "MeshAssets.h"

								namespace Data
								{
									/*
										This file has been auto-generated

										DO NOT CHANGE
									*/
									struct Assets
									{
								)");
		}

		void FinalizeAssetsFile(Ptr<File> directAssets)
		{
			directAssets->Write(R"(
									};
									const Assets Ast;
								}
								)");
		}
	}
}