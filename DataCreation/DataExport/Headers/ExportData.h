#pragma once

#include "Core/Headers/ListDefs.h"
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

		// none of the below should be here, but for the sake of getting this running without re-configuring
		// the whole mesh/mat export data sequence
		void DirectMeshes(Ptr<File> directAssets, List<String> meshes);
		void DirectMaterials(Ptr<File> directAssets, List<String> materials);

		void ExportDirectReference_Open(String name, String acronym, Ptr<File> directAssets);
		void ExportDirectReference_Close(String name, String acronym, Ptr<File> directAssets);
	}
}