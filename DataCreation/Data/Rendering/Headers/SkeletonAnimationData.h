#pragma once

#include "Core/Headers/ListDefs.h"
#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/Quaternion.h"

using namespace Core;
using namespace Core::Math;

namespace Data
{
	namespace Rendering
	{
		struct PositionFrameData
		{
			Float3 Position;
			Second Time;

			PositionFrameData() = delete;
			PositionFrameData(Float3 position, Second time);
		};

		struct RotationFrameData
		{
			FQuaternion Rotation;
			Second Time;

			RotationFrameData() = delete;
			RotationFrameData(FQuaternion rotation, Second time);
		};

		struct ScaleFrameData
		{
			Float3 Scale;
			Second Time;

			ScaleFrameData() = delete;
			ScaleFrameData(Float3 scale, Second time);
		};

		struct BoneAnimationData
		{
			String Name;

			List<PositionFrameData> PositionChannel;
			List<RotationFrameData> RotationChannel;
			List<ScaleFrameData> ScaleChannel;

			BoneAnimationData() = delete;
			BoneAnimationData(String name);

			void ReadAnimationData(String name, File& animationFile);

		private:
			void AddPositionFrame(Float3 position, Second time);
			void AddRotationFrame(FQuaternion rotation, Second time);
			void AddScaleFrame(Float3 scale, Second time);
		};

		struct SkeletonAnimationData
		{
			String Name;

			List<BoneAnimationData> BoneAnimations;

			Second Duration;

			SkeletonAnimationData() = default;
			SkeletonAnimationData(String fileName);
		};
	}
}