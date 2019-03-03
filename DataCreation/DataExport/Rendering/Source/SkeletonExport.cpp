#pragma once

#include "DataExport/Rendering/Headers/SkeletonExport.h"
#include "DataExport/Rendering/Headers/Utils.h"
#include "DataExport/Rendering/Headers/AssimpExtensions.h"

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
			Core::Ptr<const aiNode> rootNode = scene->mRootNode;
			Core::Ptr<const aiMesh> mesh = scene->mMeshes[meshIndex];

			if (!mesh->HasBones())
			{
				LOG("Given skeleton <<" + name + ">> does not exist");
				return;
			}

			Core::Ptr<const aiNode> rootNodeForMesh = FindRootNodeForMesh(rootNode, meshIndex);
			Core::UniquePtr<ExportNode> exportSkeleton = AllNodesForMesh(rootNode, mesh, meshIndex);

			// store values in file
			Core::IO::FilePath skeletonFilePath = Core::IO::FilePath{ GetCWD() + "/Resources/ExportedAssets/Skeletons/", ToString(HashValue(name)) + ".skl" };
			Core::IO::File skeletonFile = File(skeletonFilePath, ios::out);
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

			AddSkeletonToFile(&skeletonFile, move(exportSkeleton));

			skeletonFile.Close();
		}

		void AddSkeletonToFile(Core::Ptr<Core::IO::File> skeletonFile, Core::UniquePtr<ExportNode> exportSkeleton)
		{
			exportSkeleton->CleanStructure();
			AddNodeToFile(skeletonFile, exportSkeleton.get());
		}

		void AddNodeToFile(Core::Ptr<Core::IO::File> skeletonFile, Core::Ptr<const ExportNode> skeletonNode)
		{
			aiVector3D scaling;
			aiQuaterniont<float> rotation;
			aiVector3D position;
			skeletonNode->mTransformation.Decompose(scaling, rotation, position);

			skeletonFile->Write(String(skeletonNode->mName.C_Str()), skeletonNode->mNumChildren);

			skeletonFile->Write(", scaling", scaling.x, scaling.y, scaling.z);

			skeletonFile->Write(", rotation", rotation.x, rotation.y, rotation.z, rotation.w);

			skeletonFile->Write(", position", position.x, position.y, position.z);

			skeletonFile->CreateNewLine();

			for (uint i = 0; i < skeletonNode->mNumChildren; i++)
			{
				AddNodeToFile(skeletonFile, static_cast<Core::Ptr<ExportNode>>(skeletonNode->mChildren[i]));
			}
		}
	}
}
