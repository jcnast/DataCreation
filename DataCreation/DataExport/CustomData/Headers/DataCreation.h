#pragma once

#include "Core/IO/Headers/File.h"

#include "DataExport/SQL/Headers/SQLInstance.h"

#include "DataExport/CustomData/Headers/DataExportDefs.h"

using namespace Core;
using namespace Core::IO;

using namespace Data;
using namespace Data::SQL;

namespace Data
{
	namespace DataExport
	{
		void ExportCustomData(Ptr<SQLInstance> db, Ptr<File> directAssets);

		void ExportDataTypeInformation(Ptr<SQLInstance> db, String type, Ptr<File> customAssets, Ptr<File> directAssets);

		UniquePtr<DataType> ExportDataType(String sql, Ptr<File> customAssets);
		void ExportDataForType(Ptr<SQLInstance> db, UniquePtr<DataType> type, Ptr<File> directAssets);

		void ExportDirectReference_Open(String name, Ptr<File> directAssets);
		void ExportDirectReference_Close(String name, Ptr<File> directAssets);
		void ExportDataItemForType(MetaAssetData asset, FilePath exportTo, Ptr<File> directAssets);

		void InitializeCustomAssetFile(Ptr<File> customAssets);
		void FinalizeCustomAssetFile(Ptr<File> customAssets);
	}
}