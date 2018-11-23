#pragma once

#include "DataExport/Rendering/Headers/SkeletonExport.h"
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
		void CreateFileForSkeleton(Core::Ptr<Core::IO::File> directAssets, Ptr<const aiScene> scene, uint meshIndex, String name)
		{
			Ptr<const aiNode> rootNode = scene->mRootNode;
			Ptr<const aiMesh> mesh = scene->mMeshes[meshIndex];

			if (!mesh->HasBones())
			{
				LOG("Given skeleton <<" + name + ">> does not exist");
				return;
			}

			Ptr<const aiNode> rootNodeForMesh = FindRootNodeForMesh(rootNode, meshIndex);
			List<Ptr<const aiNode>> skeletonNodes = AllNodesForMesh(rootNode, mesh, meshIndex);

			// store values in file
			FilePath skeletonFilePath = FilePath{ GetCWD() + "/Resources/ExportedAssets/Skeletons/", ToString(HashValue(name)) + ".skl" };
			File skeletonFile = File(skeletonFilePath, ios::out);
			skeletonFile.Open();

			if (!skeletonFile.FileStream.is_open())
			{
				LOG("Could not open file <<" + skeletonFilePath.GetFullPath() + ">>");
				return;
			}

			skeletonFile.Write("animations", scene->mNumAnimations);
			skeletonFile.CreateNewLine();
			for (uint animationIndex = 0; animationIndex < scene->mNumAnimations; animationIndex++)
			{
				skeletonFile.Write(ToString(HashValue(String(scene->mAnimations[animationIndex]->mName.C_Str())).H));
				skeletonFile.CreateNewLine();
			}

			AddNodeToFile(&skeletonFile, rootNodeForMesh, 0, skeletonNodes);

			skeletonFile.Close();
		}

		void AddNodeToFile(Ptr<File> skeletonFile, Ptr<const aiNode> rootNode, uint depth, List<Ptr<const aiNode>>& skeletonNodes)
		{
			if (!InList(skeletonNodes, rootNode))
			{
				return;
			}

			aiVector3D scaling;
			aiQuaterniont<float> rotation;
			aiVector3D position;
			rootNode->mTransformation.Decompose(scaling, rotation, position);

			skeletonFile->Write(String(rootNode->mName.C_Str()), depth);

			skeletonFile->Write(", scaling", scaling.x, scaling.y, scaling.z);

			skeletonFile->Write(", rotation", rotation.x, rotation.y, rotation.z, rotation.w);

			skeletonFile->Write(", position", position.x, position.y, position.z);

			skeletonFile->CreateNewLine();

			for (int i = 0; i < rootNode->mNumChildren; i++)
			{
				AddNodeToFile(skeletonFile, rootNode->mChildren[i], depth + 1, skeletonNodes);
			}
		}
	}
}
