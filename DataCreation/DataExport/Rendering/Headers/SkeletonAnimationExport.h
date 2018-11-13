#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/ListDefs.h"

#include "Core/IO/Headers/File.h"

struct aiScene;
struct aiMesh;
struct aiNode;
struct aiNodeAnim;
struct aiAnimation;

namespace Data
{
	namespace DataExport
	{
		void CreateFileForSkeletonAnimation(Core::Ptr<Core::IO::File> directAssets, Core::Ptr<aiAnimation> animation, Ptr<const aiNode> rootNode, Ptr<const aiMesh> mesh, uint meshIndex, String name);

		void AddChannelToFile(Core::Ptr<Core::IO::File> skeletonAnimationFile, Core::Ptr<const aiNodeAnim> channel);
		Core::String BehaviourToString(aiAnimBehaviour behaviour);
	}
}
