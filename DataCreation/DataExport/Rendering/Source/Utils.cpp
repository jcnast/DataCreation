#pragma once

#include "DataExport/Rendering/Headers/Utils.h"

#include "Core/Headers/Hash.h"

#include "Core/Debugging/Headers/Macros.h"

#include "Core/IO/Headers/File.h"
#include "Core/IO/Headers/Folder.h"
#include "Core/IO/Headers/IOUtils.h"

#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/Quaternion.h"

#include "ASSIMP/cimport.h"
#include "ASSIMP/scene.h"
#include "ASSIMP/postprocess.h"

using namespace std;
using namespace Core;
using namespace Core::IO;
using namespace Core::Math;

namespace Data
{
	namespace DataExport
	{
		Ptr<const aiNode> FindRootNodeForMesh(Ptr<const aiNode> rootNode, uint meshIndex)
		{
			Ptr<const aiNode> meshNode = FindNodeForMesh(rootNode, meshIndex);

			if (meshNode == nullptr)
			{
				return rootNode;
			}

			if (meshNode->mParent != nullptr)
			{
				return meshNode->mParent;
			}

			return meshNode;
		}

		Ptr<const aiNode> FindNodeForMesh(Ptr<const aiNode> rootNode, uint meshIndex)
		{
			for (uint i = 0; i < rootNode->mNumMeshes; i++)
			{
				if (rootNode->mMeshes[i] == meshIndex)
				{
					return rootNode;
				}
			}

			for (uint i = 0; i < rootNode->mNumChildren; i++)
			{
				Ptr<const aiNode> rootNodeForMesh = FindNodeForMesh(rootNode->mChildren[i], meshIndex);
				if (rootNodeForMesh != nullptr)
				{
					return rootNodeForMesh;
				}
			}

			return nullptr;
		}

		Ptr<const aiNode> FindNodeWithName(Ptr<const aiNode> rootNode, String name)
		{
			if (rootNode->mName == aiString(name))
			{
				return rootNode;
			}

			for (uint i = 0; i < rootNode->mNumChildren; i++)
			{
				Ptr<const aiNode> nodeWtihName = FindNodeWithName(rootNode->mChildren[i], name);
				if (nodeWtihName != nullptr)
				{
					return nodeWtihName;
				}
			}

			return nullptr;
		}

		Core::List<Core::Ptr<const aiNode>> AllNodesForMesh(Core::Ptr<const aiNode> rootNode, Ptr<const aiMesh> mesh, Core::uint meshIndex)
		{
			Ptr<const aiNode> rootNodeForMesh = FindRootNodeForMesh(rootNode, meshIndex);
			List<Ptr<const aiNode>> skeletonNodes;

			for (uint i = 0; i < mesh->mNumBones; i++)
			{
				Ptr<const aiNode> nodeForBone = FindNodeWithName(rootNodeForMesh, String(mesh->mBones[i]->mName.C_Str()));
				AddMissingNodesToList(skeletonNodes, nodeForBone, rootNodeForMesh);
			}

			return skeletonNodes;
		}

		void AddMissingNodesToList(Core::List<Core::Ptr<const aiNode>>& list, Core::Ptr<const aiNode> start, Core::Ptr<const aiNode> end)
		{
			if (start == nullptr || end == nullptr)
			{
				LOG("node pointers to add to list of nodes in skeleton are nullptrs!");
				return;
			}

			if (InList(list, start))
			{
				return;
			}

			Push(list, start);

			if (start != end)
			{
				AddMissingNodesToList(list, start->mParent, end);
			}
		}
	}
}
