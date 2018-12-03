#include "DataExport/Headers/ExportData.h"

#include "Core/Debugging/Headers/Macros.h"

#include "Core/Headers/Hash.h"

#include "Core/IO/Headers/IOUtils.h"
#include "Core/IO/Headers/Folder.h"

#include "DataExport/CustomData/Headers/DataCreation.h"

#include "DataExport/Rendering/Headers/SceneConversion.h"

namespace Data
{
	namespace DataExport
	{
		void ExportData()
		{
			LOG("Starting to export data");
			auto directPath = FilePath{ GetCWD() + "Resources/ExportedAssets/", String("Assets.h") };
			auto directAssets = File(directPath, ios::out);
			directAssets.Open();
			directAssets.Clear();

			InitializeAssetsFile(&directAssets);

			// Not exporting custom data since it is not needed atm
			//ExportCustomData(&directAssets);
			ExportRenderingData(&directAssets);

			FinalizeAssetsFile(&directAssets);

			directAssets.Close();
			LOG("Finished exporting data");
		}

		void ExportCustomData(Ptr<File> directAssets)
		{
			CreateFolder(GetCWD() + "Resources/ExportedAssets/CustomData");

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

			// maybe this should be it's own function?
			CreateFolder(GetCWD() + "Resources/ExportedAssets/Models");
			CreateFolder(GetCWD() + "Resources/ExportedAssets/Materials");
			CreateFolder(GetCWD() + "Resources/ExportedAssets/Meshes");
			CreateFolder(GetCWD() + "Resources/ExportedAssets/Skeletons");
			CreateFolder(GetCWD() + "Resources/ExportedAssets/SkeletonAnimations");
			CreateFolder(GetCWD() + "Resources/ExportedAssets/Textures");

			// in the future, this should likely also reference a database that is used to get specific file locations
			FilePath WomanPath = FilePath{ GetCWD() + "Resources/ImportedAssets/Models/Woman/", "Woman.fbx" };
			File WomanFile = File(WomanPath, ios::in);
			ConvertModelsInFolder(directAssets, GetCWD() + "Resources/ImportedAssets/Models/");

			LOG("Finished exporting rendering data");
		}

		void InitializeAssetsFile(Ptr<File> directAssets)
		{
			auto header = R"(
#pragma once

#include "Data/Headers/AssetType.h"
#include "Data/Headers/AssetName.h"

#include "CustomAssets.h"

#include "Data/Rendering/Headers/AnimatedMeshData.h"
#include "Data/Rendering/Headers/AnimatedModelData.h"
#include "Data/Rendering/Headers/MaterialData.h"
#include "Data/Rendering/Headers/SkeletonAnimationData.h"
#include "Data/Rendering/Headers/SkeletonData.h"
#include "Data/Rendering/Headers/StaticMeshData.h"
#include "Data/Rendering/Headers/StaticModelData.h"
#include "Data/Rendering/Headers/TextureData.h"

namespace Data
{
	/*
		This file has been auto-generated

		DO NOT CHANGE
	*/
	struct Assets
	{
)";
			directAssets->Write(header);
		}

		void FinalizeAssetsFile(Ptr<File> directAssets)
		{
			auto footer = R"(
	};
	const Assets Ast;
	}
)";
			directAssets->Write(footer);
		}

		// none of the below should be here, but for the sake of getting this running without re-configuring
		// the whole mesh/mat export data sequence		
		void ExportDirectReference_Open(String name, String acronym, Ptr<File> directAssets)
		{
			directAssets->Write("\t\tstruct " + name);
			directAssets->CreateNewLine();
			directAssets->Write("\t\t{");
			directAssets->CreateNewLine();
		}

		void ExportDirectReference_Close(String name, String acronym, Ptr<File> directAssets)
		{
			directAssets->Write("\t\t};");
			directAssets->CreateNewLine();
			directAssets->Write("\t\tconst " + name + " " + acronym + ";");
			directAssets->CreateNewLine();
		}
	}
}