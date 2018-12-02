#pragma once

#include "DataExport/Rendering/Headers/SkeletonAnimationExport.h"
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

using namespace Core;
using namespace Core::IO;
using namespace Core::Math;

namespace Data
{
	namespace DataExport
	{
		void CreateFileForSkeletonAnimation(Core::Ptr<Core::IO::File> directAssets, Core::Ptr<aiAnimation> animation, Ptr<const aiNode> rootNode, Ptr<const aiMesh> mesh, uint meshIndex, String name)
		{
			if (animation == nullptr)
			{
				LOG("Given skeleton <<" + name + ">> does not exist");
				return;
			}

			Ptr<const aiNode> rootNodeForMesh = FindRootNodeForMesh(rootNode, meshIndex);
			List<Ptr<const aiNode>> skeletonNodes = AllNodesForMesh(rootNode, mesh, meshIndex);

			// store values in file
			FilePath skeletonAnimationFilePath = FilePath{ GetCWD() + "/Resources/ExportedAssets/SkeletonAnimations/", ToString(HashValue(name + String(animation->mName.C_Str()))) + ".sanim" };
			File skeletonAnimationFile = File(skeletonAnimationFilePath, ios::out);
			skeletonAnimationFile.Open();

			if (!skeletonAnimationFile.FileStream.is_open())
			{
				LOG("Could not open file <<" + skeletonAnimationFile.GetFullPath() + ">>");
				return;
			}

			skeletonAnimationFile.Write(String(animation->mName.C_Str()), animation->mNumChannels, animation->mDuration / animation->mTicksPerSecond);
			skeletonAnimationFile.CreateNewLine();

			for (uint i = 0; i < animation->mNumChannels; i++)
			{
				if (InList(skeletonNodes, FindNodeWithName(rootNode, String(animation->mChannels[i]->mNodeName.C_Str()))))
				{
					AddChannelToFile(&skeletonAnimationFile, animation->mChannels[i], animation->mTicksPerSecond);
				}
			}

			skeletonAnimationFile.Close();
		}

		void AddChannelToFile(Core::Ptr<Core::IO::File> skeletonAnimationFile, Core::Ptr<const aiNodeAnim> channel, double ticksPerSecond)
		{
			skeletonAnimationFile->CreateNewLine();
			skeletonAnimationFile->Write(String(channel->mNodeName.C_Str()));

			skeletonAnimationFile->CreateNewLine();
			skeletonAnimationFile->Write("preState", BehaviourToString(channel->mPreState));
			skeletonAnimationFile->CreateNewLine();
			skeletonAnimationFile->Write("postState", BehaviourToString(channel->mPostState));

			skeletonAnimationFile->CreateNewLine();
			skeletonAnimationFile->Write("position", channel->mNumPositionKeys);
			for (uint i = 0; i < channel->mNumPositionKeys; i++)
			{
				const aiVectorKey& key = channel->mPositionKeys[i];
				skeletonAnimationFile->CreateNewLine();
				skeletonAnimationFile->Write(key.mTime / ticksPerSecond, key.mValue.x, key.mValue.y, key.mValue.z);
			}

			skeletonAnimationFile->CreateNewLine();
			skeletonAnimationFile->Write("scale", channel->mNumScalingKeys);
			for (uint i = 0; i < channel->mNumScalingKeys; i++)
			{
				const aiVectorKey& key = channel->mScalingKeys[i];
				skeletonAnimationFile->CreateNewLine();
				skeletonAnimationFile->Write(key.mTime / ticksPerSecond, key.mValue.x, key.mValue.y, key.mValue.z);
			}

			skeletonAnimationFile->CreateNewLine();
			skeletonAnimationFile->Write("rotation", channel->mNumRotationKeys);
			for (uint i = 0; i < channel->mNumRotationKeys; i++)
			{
				const aiQuatKey& key = channel->mRotationKeys[i];
				skeletonAnimationFile->CreateNewLine();
				skeletonAnimationFile->Write(key.mTime / ticksPerSecond, key.mValue.x, key.mValue.y, key.mValue.z, key.mValue.w);
			}
		}

		Core::String BehaviourToString(aiAnimBehaviour behaviour)
		{
			switch (behaviour)
			{
				case aiAnimBehaviour_CONSTANT:
				{
					return "constant";
				}
				case aiAnimBehaviour_DEFAULT:
				{
					return "default";
				}
				case aiAnimBehaviour_LINEAR:
				{
					return "linear";
				}
				case aiAnimBehaviour_REPEAT:
				{
					return "repeat";
				}
				default:
				{
					return "unknown";
				}
			}
		}
	}
}
