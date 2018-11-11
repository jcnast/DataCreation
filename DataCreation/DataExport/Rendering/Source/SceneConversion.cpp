#include "DataExport\Rendering\Headers\SceneConversion.h"

#include "DataExport/Rendering/Headers/MeshExport.h"
#include "DataExport/Rendering/Headers/MaterialExport.h"
#include "DataExport/Rendering/Headers/SkeletonExport.h"

#include "Core/Headers/ListDefs.h"
#include "Core/Headers/Hash.h"

#include "Core/Debugging/Headers/Macros.h"

#include "Core/IO/Headers/Folder.h"
#include "Core/IO/Headers/IOUtils.h"

#include "ASSIMP/cimport.h"
#include "ASSIMP/scene.h"
#include "ASSIMP/postprocess.h"
#include "ASSIMP/material.h"

using namespace Core;
using namespace Core::IO;

namespace Data
{
	namespace DataExport
	{
		void ConvertModelsInFolder(Ptr<File> directAssets, Ptr<File> sceneFile, String sceneName)
		{
			// in the future, this should likely also reference a database that is used to get specific file locations
			ConvertFilesForScene(directAssets, sceneFile, sceneName);
		}

		void ConvertFilesForScene(Ptr<File> directAssets, Ptr<File> sceneFile, String sceneName)
		{
			LOG("Converting files for <<" + sceneFile->GetFullPath() + ">>");
			// this process preset also INCLUDES the flag to make all faces based on triangles
			String fullPathCopy = sceneFile->GetFullPath();
			Ptr<const char> c_Path = fullPathCopy.c_str();
			const aiScene* loadedScene = aiImportFile(c_Path, aiProcessPreset_TargetRealtime_MaxQuality);

			if (!loadedScene)
			{
				LOG("Could not load file <<" + sceneFile->GetFullPath() + ">>");
				LOG("ASSIMP ERROR: " + String(aiGetErrorString()));
				return;
			}

			uint32_t numberOfMeshes = loadedScene->mNumMeshes;

			for (uint32_t meshIndex = 0u; meshIndex < numberOfMeshes; meshIndex++)
			{
				LOG("Creating file to hold mesh information for <<" + sceneName + ">>");
				CreateFileForMesh(directAssets, loadedScene->mMeshes[meshIndex], sceneName);
				LOG("Creating file to hold material information for <<" + sceneName + ">>");
				CreateFileForMaterial(directAssets, loadedScene->mMaterials[loadedScene->mMeshes[meshIndex]->mMaterialIndex], sceneName);

				if (loadedScene->mMeshes[meshIndex]->HasBones)
				{
					LOG("Creating file to hold skeleton information for <<" + sceneName + ">>");
					CreateFileForSkeleton(directAssets, loadedScene->mRootNode, loadedScene->mMeshes[meshIndex], sceneName);
				}
				else
				{
					LOG("<<" + sceneName + ">> does not have any skeletal information");
				}
			}

			LOG("Releasing memory for loading scene <<" + sceneFile->GetFullPath() + ">>");
			// needs to be done since assimp holds all of the memeory management for loading
			aiReleaseImport(loadedScene);
		}
	}
}
