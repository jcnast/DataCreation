#pragma once

#include "Core/Headers/ListDefs.h"
#include "Core/Headers/PtrDefs.h"

#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/Quaternion.h"

#include "Core/IO/Headers/File.h"
#include "Core/IO/Headers/IODefs.h"

using namespace Core;
using namespace Core::Math;

namespace Data
{
	namespace Rendering
	{
		struct SkeletonBoneData
		{
			String Name;
			Float3 Position;
			FQuaternion Rotation;

			List<UniquePtr<SkeletonBoneData>> ChildBones;

			SkeletonBoneData() = delete;
			SkeletonBoneData(String name, Float3 position, FQuaternion rotation = FQuaternion());

			void AddBone(UniquePtr<SkeletonBoneData> bone);
		};

		struct SkeletonData
		{
			UniquePtr<SkeletonBoneData> Root;

			SkeletonData() = default;
			SkeletonData(String fileName);

		private:
			void ReadBoneChildren(Ptr<SkeletonBoneData> parent, File& skeletonFile);

			void ReadName(IOSStreamChar& lineStream, String& name);
			void ReadPosition(IOSStreamChar& lineStream, Float3& position);
			void ReadRotation(IOSStreamChar& lineStream, FQuaternion& rotation);
		};
	}
}