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

		/*
		void CreateTextureForMesh(const aiMesh* mesh, int textureIndex);
		*/
	}
}
