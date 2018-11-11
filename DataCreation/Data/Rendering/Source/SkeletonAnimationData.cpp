#include "Data/Rendering/Headers/SkeletonAnimationData.h"

#include "Core/IO/Headers/IOUtils.h"

#include "Core/Debugging/Headers/Macros.h"

using namespace Core;
using namespace Core::IO;

namespace Data
{
	namespace Rendering
	{
		PositionFrameData::PositionFrameData(Float3 position, Second time)
			: Position(position)
			, Time(time)
		{

		}

		RotationFrameData::RotationFrameData(FQuaternion rotation, Second time)
			: Rotation(rotation)
			, Time(time)
		{

		}

		ScaleFrameData::ScaleFrameData(Float3 scale, Second time)
			: Scale(scale)
			, Time(time)
		{

		}

		BoneAnimationData::BoneAnimationData(String name)
			: Name(name)
		{

		}

		void BoneAnimationData::ReadAnimationData(String name, File& animationFile)
		{
			String line = animationFile.GetLine();

			IOSStreamChar lineStream(line);

			bool doneReading = false;

			String word;
			int frames;
			while (!doneReading)
			{
				lineStream >> word;
				lineStream >> frames;

				if (word == "position")
				{
					for (int i = 0; i < frames; i++)
					{
						Float3 position;
						Second time;

						lineStream >> position.X;
						lineStream >> position.Y;
						lineStream >> position.Z;

						lineStream >> time.count;

						AddPositionFrame(position, time);
					}
					continue;
				}
				else if (word == "rotation")
				{
					for (int i = 0; i < frames; i++)
					{
						FQuaternion rotation;
						Second time;

						lineStream >> rotation.X;
						lineStream >> rotation.Y;
						lineStream >> rotation.Z;
						lineStream >> rotation.W;

						lineStream >> time.count;

						AddRotationFrame(rotation, time);
					}
					continue;
				}
				else if (word == "scale")
				{
					for (int i = 0; i < frames; i++)
					{
						Float3 scale;
						Second time;

						lineStream >> scale.X;
						lineStream >> scale.Y;
						lineStream >> scale.Z;

						lineStream >> time.count;

						AddScaleFrame(scale, time);
					}
					continue;
				}

				doneReading = true;
			}
		}

		void BoneAnimationData::AddPositionFrame(Float3 position, Second time)
		{
			Push(PositionChannel, PositionFrameData(position, time));
		}

		void BoneAnimationData::AddRotationFrame(FQuaternion rotation, Second time)
		{
			Push(RotationChannel, RotationFrameData(rotation, time));
		}

		void BoneAnimationData::AddScaleFrame(Float3 scale, Second time)
		{
			Push(ScaleChannel, ScaleFrameData(scale, time));
		}

		SkeletonAnimationData::SkeletonAnimationData(String fileName)
		{
			File animationFile = OpenFileI(FilePath{ String("PATH TO FILE"), fileName });

			MESSAGE(animationFile.FileStream.is_open(), "FAILED TO READ FILE <<" + fileName + ">>");

			try
			{
				String line = animationFile.GetLine();

				IOSStreamChar lineStream(line);

				int animationCount;

				lineStream >> animationCount;

				String animationName;
				for (int i = 0; i < animationCount; i++)
				{
					lineStream >> animationName;

					BoneAnimationData newBoneAnimation = BoneAnimationData("UnNamed");
					newBoneAnimation.ReadAnimationData(animationName, animationFile);

					Push(BoneAnimations, newBoneAnimation);
				}
			}
			catch (EOFException& e)
			{
				std::cout << e.GetError() << std::endl;
				return;
			}
		}
	}
}