#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/IO/Headers/File.h"

using namespace std;

struct aiScene;
struct aiMesh;
struct aiMaterial;

namespace Data
{
	namespace DataExport
	{
		void ConvertModelsInFolder(Core::Ptr<Core::IO::File> directAssets, Core::Ptr<Core::IO::File> sceneFile, Core::String sceneName);

		void ConvertFilesForScene(Core::Ptr<Core::IO::File> directAssets, Core::Ptr<Core::IO::File> sceneFile, Core::String sceneName);

		void CreateFileForMesh(Core::Ptr<Core::IO::File> directAssets, Core::String sceneName, const aiScene* loadedScene, const aiMesh* mesh, uint32_t meshIndex, bool usesTexture);
		void CreateFileForMaterial(Core::Ptr<Core::IO::File> directAssets, Core::String sceneName, const aiMaterial* material, uint32_t materialIndex);

		// to be done later (or something like them):
		/*
		void CreateImageForMesh(const aiMesh* mesh, int imageIndex);
		void ConvertAnimationsToFile(const aiScene* scene, int animationIndex);
		*/
	}
}
