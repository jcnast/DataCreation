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
		struct ExportNode;

		void CreateFileForSkeleton(Core::Ptr<Core::IO::File> directAssets, Core::Ptr<const aiScene> scene, Core::uint meshIndex, Core::String name);

		void AddSkeletonToFile(Core::Ptr<Core::IO::File> skeletonFile, Core::UniquePtr<ExportNode> exportSkeleton);

		void AddNodeToFile(Core::Ptr<Core::IO::File> skeletonFile, Core::Ptr<const ExportNode> rootNode);
	}
}
