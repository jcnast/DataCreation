#pragma once

#include "Core/IO/Headers/File.h"
#include "Core/Headers/PtrDefs.h"

using namespace Core;
using namespace Core::IO;

namespace Data
{
	namespace DataExport
	{
		void ExportData();

		void ExportCustomData(Ptr<File> directAssets);
		void ExportRenderingData(Ptr<File> directAssets);

		void InitializeAssetsFile(Ptr<File> directAssets);
		void FinalizeAssetsFile(Ptr<File> directAssets);
	}
}