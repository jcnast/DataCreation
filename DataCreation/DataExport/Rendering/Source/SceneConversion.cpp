#include "DataExport\Rendering\Headers\SceneConversion.h"

#include "DataExport/Headers/ExportData.h"

#include "DataExport/Rendering/Headers/ModelExport.h"
#include "DataExport/Rendering/Headers/MeshExport.h"
#include "DataExport/Rendering/Headers/MaterialExport.h"
#include "DataExport/Rendering/Headers/SkeletonExport.h"
#include "DataExport/Rendering/Headers/SkeletonAnimationExport.h"

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
		void ConvertModelsInFolder(Ptr<File> directAssets, String folder)
		{
			List<String> models;
			List<String> meshes;
			List<String> materials;
			List<String> skeletons;
			List<String> skeletonAnimations;

			List<String> importedAssets = AllFilesInFolder(folder, true);

			// in the future, this should likely also reference a database that is used to get specific file locations
			for (String asset : importedAssets)
			{
				Core::size dotIndex = asset.find_last_of('.');
				if (dotIndex == -1)
				{
					return;
				}

				String assetType = asset.substr(dotIndex, asset.length() - dotIndex);
				String assetName = asset.substr(0, dotIndex);

				if (assetType != ".fbx")
				{
					return;
				}

				FilePath assetPath = FilePath{ GetCWD() + folder, asset };
				File assetFile = File(assetPath, ios::in);
				ConvertFilesForScene(directAssets, &assetFile, assetName, models, meshes, materials, skeletons, skeletonAnimations);
			}

			DirectModels(directAssets, models);
			DirectMeshes(directAssets, meshes);
			DirectMaterials(directAssets, materials);
			DirectSkeletons(directAssets, skeletons);
			DirectSkeletonAnimations(directAssets, skeletonAnimations);
		}

		void ConvertFilesForScene(Ptr<File> directAssets, Ptr<File> sceneFile, String sceneName, List<String> models, List<String> meshes, List<String> materials, List<String> skeletons, List<String> skeletonAnimations)
		{
			LOG("Converting files for <<" + sceneFile->GetFullPath() + ">>");
			// this process preset also INCLUDES the flag to make all faces based on triangles
			String fullPathCopy = sceneFile->GetFullPath();
			Ptr<const char> c_Path = fullPathCopy.c_str();
			Ptr<const aiScene> loadedScene = aiImportFile(c_Path, aiProcessPreset_TargetRealtime_MaxQuality);

			if (!loadedScene)
			{
				LOG("Could not load file <<" + sceneFile->GetFullPath() + ">>");
				LOG("ASSIMP ERROR: " + String(aiGetErrorString()));
				return;
			}

			uint32_t numberOfMeshes = loadedScene->mNumMeshes;

			// Create model scene that holds references to all other data types (mesh, mat, skl, sanim, texture - eventually)
			// Create a file for each mesh in the parent mesh
			for (uint32_t meshIndex = 0u; meshIndex < numberOfMeshes; meshIndex++)
			{
				String fileName = sceneName + "_" + ToString(meshIndex);

				LOG("Creating file to hold model information for <<" + fileName + ">>");
				CreateFileForModel(directAssets, loadedScene, meshIndex, fileName);
				Push(models, fileName);

				LOG("Creating file to hold mesh information for <<" + fileName + ">>");
				CreateFileForMesh(directAssets, loadedScene->mMeshes[meshIndex], fileName);
				Push(meshes, fileName);

				LOG("Creating file to hold material information for <<" + fileName + ">>");
				CreateFileForMaterial(directAssets, loadedScene->mMaterials[loadedScene->mMeshes[meshIndex]->mMaterialIndex], fileName);
				Push(materials, fileName);

				if (loadedScene->mMeshes[meshIndex]->HasBones())
				{
					LOG("Creating file to hold skeleton information for <<" + fileName + ">>");
					CreateFileForSkeleton(directAssets, loadedScene, meshIndex, fileName);
					Push(skeletons, fileName);

					for (uint animationIndex = 0; animationIndex < loadedScene->mNumAnimations; animationIndex++)
					{
						LOG("Creating file to hold skeleton animation information for <<" + fileName + ">>");
						// do this before the skeleton so the skeleton knows (and saves) its animations?
						CreateFileForSkeletonAnimation(directAssets, loadedScene->mAnimations[animationIndex], loadedScene->mRootNode, loadedScene->mMeshes[meshIndex], meshIndex, fileName);
						Push(skeletonAnimations, fileName + "_" + String(loadedScene->mAnimations[animationIndex]->mName.C_Str()));
					}
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

		void DirectModels(Ptr<File> directAssets, List<String> models)
		{
			ExportDirectReference_Open("Models", "Mdl", directAssets);

			for (auto& model : models)
			{
				directAssets->Write("\t\t\tconst AssetName<Rendering::ModelData> " + model + " = " + ToString(HashValue(model).H) + ";");
				directAssets->CreateNewLine();
			}

			ExportDirectReference_Close("Models", "Mdl", directAssets);
		}

		void DirectMeshes(Ptr<File> directAssets, List<String> meshes)
		{
			ExportDirectReference_Open("Meshes", "Msh", directAssets);

			for (auto& mesh : meshes)
			{
				directAssets->Write("\t\t\tconst AssetName<Rendering::MeshData> " + mesh + " = " + ToString(HashValue(mesh).H) + ";");
				directAssets->CreateNewLine();
			}

			ExportDirectReference_Close("Meshes", "Msh", directAssets);
		}

		void DirectMaterials(Ptr<File> directAssets, List<String> materials)
		{
			ExportDirectReference_Open("Materials", "Mat", directAssets);

			for (auto& material : materials)
			{
				directAssets->Write("\t\t\tconst AssetName<Rendering::MaterialData> " + material + " = " + ToString(HashValue(material).H) + ";");
				directAssets->CreateNewLine();
			}

			ExportDirectReference_Close("Materials", "Mat", directAssets);
		}

		void DirectSkeletons(Ptr<File> directAssets, List<String> skeletons)
		{
			ExportDirectReference_Open("Skeletons", "Skl", directAssets);

			for (auto& skeleton : skeletons)
			{
				directAssets->Write("\t\t\tconst AssetName<Rendering::SkeletonData> " + skeleton + " = " + ToString(HashValue(skeleton).H) + ";");
				directAssets->CreateNewLine();
			}

			ExportDirectReference_Close("Skeletons", "Skl", directAssets);
		}

		void DirectSkeletonAnimations(Ptr<File> directAssets, List<String> skeletonAnimations)
		{
			ExportDirectReference_Open("SkeletonAnimations", "SAnim", directAssets);

			for (auto& skeletonAnimation : skeletonAnimations)
			{
				directAssets->Write("\t\t\tconst AssetName<Rendering::SkeletonAnimationData> " + skeletonAnimation + " = " + ToString(HashValue(skeletonAnimation).H) + ";");
				directAssets->CreateNewLine();
			}

			ExportDirectReference_Close("SkeletonAnimations", "SAnim", directAssets);
		}
	}
}
