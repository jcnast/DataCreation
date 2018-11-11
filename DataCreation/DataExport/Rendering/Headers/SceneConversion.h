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

		// to be done later (or something like them):
		/*
		void CreateSkeletonForModel();
		void CreateFileForSkeleton();

		// will need node hierarchy and mesh for skeleton
		void CreateAnimationsForSkeleton();
		void ConvertAnimationsToFile(const aiScene* scene, int animationIndex);

		void CreateTextureForMesh(const aiMesh* mesh, int textureIndex);
		*/
	}
}
