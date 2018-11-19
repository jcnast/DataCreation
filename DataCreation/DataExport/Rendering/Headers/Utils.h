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
		Core::Ptr<const aiNode> FindRootNodeForMesh(Core::Ptr<const aiNode> rootNode, Core::uint meshIndex);
		Core::Ptr<const aiNode> FindNodeForMesh(Core::Ptr<const aiNode> rootNode, Core::uint meshIndex);
		Core::Ptr<const aiNode> FindNodeWithName(Core::Ptr<const aiNode> rootNode, Core::String name);

		Core::List<Core::Ptr<const aiNode>> AllNodesForMesh(Core::Ptr<const aiNode> rootNode, Core::Ptr<const aiMesh> mesh, Core::uint meshIndex);

		void AddMissingNodesToList(Core::List<Core::Ptr<const aiNode>>& list, Core::Ptr<const aiNode> start, Core::Ptr<const aiNode> end);
	}
}
