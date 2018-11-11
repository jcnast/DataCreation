#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/IO/Headers/File.h"

struct aiScene;
struct aiMesh;
struct aiMaterial;

namespace Data
{
	namespace DataExport
	{
		void CreateFileForSkeleton(Core::Ptr<Core::IO::File> directAssets, Ptr<const aiNode> rootNode, Ptr<const aiMesh> mesh, String name);
	}
}
