#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/ListDefs.h"

#include "Core/IO/Headers/File.h"

struct aiScene;
struct aiMesh;
struct aiNode;

namespace Data
{
	namespace DataExport
	{
		void CreateFileForSkeleton(Core::Ptr<Core::IO::File> directAssets, Ptr<const aiNode> rootNode, Ptr<const aiMesh> mesh, uint meshIndex, String name);

		void AddNodeToFile(Core::Ptr<Core::IO::File> skeletonFile, Core::Ptr<const aiNode> rootNode, uint depth, Core::List<Core::Ptr<const aiNode>>& skeletonNodes);
	}
}
