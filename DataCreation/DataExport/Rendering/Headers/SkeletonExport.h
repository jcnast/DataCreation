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
		void CreateFileForSkeleton(Core::Ptr<Core::IO::File> directAssets, Core::Ptr<const aiScene> scene, Core::uint meshIndex, Core::String name);

		void AddNodeToFile(Core::Ptr<Core::IO::File> skeletonFile, Core::Ptr<const aiNode> rootNode, Core::uint depth, Core::List<Core::Ptr<const aiNode>>& skeletonNodes);
	}
}
