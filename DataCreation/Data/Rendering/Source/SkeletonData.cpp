#include "Data/Rendering/Headers/SkeletonData.h"

#include "Core/IO/Headers/IOUtils.h"

#include "Core/Debugging/Headers/Macros.h"

using namespace Core;
using namespace Core::IO;

namespace Data
{
	namespace Rendering
	{
		SkeletonBoneData::SkeletonBoneData(String name, Float3 position, FQuaternion rotation = FQuaternion())
			: Name(name)
			, Position(position)
			, Rotation(rotation)
		{
		}

		void SkeletonBoneData::AddBone(UniquePtr<SkeletonBoneData> bone)
		{
			Push(ChildBones, move(bone));
		}

		SkeletonData::SkeletonData(String fileName)
		{
			File skeletonFile = OpenFileI(FilePath{ String("PATH TO FILE"), fileName });

			MESSAGE(skeletonFile.FileStream.is_open(), "FAILED TO READ FILE <<" + fileName + ">>");

			try
			{
				String line = skeletonFile.GetLine();

				IOSStreamChar lineStream(line);
				Float3 position;
				FQuaternion rotation;

				int children;

				ReadPosition(lineStream, position);
				ReadRotation(lineStream, rotation);

				lineStream >> children;

				Root = MakeUnique<SkeletonBoneData>("Root", position, rotation);

				for (int i = 0; i < children; i++)
				{
					ReadBoneChildren(Root.get(), skeletonFile);
				}
			}
			catch (EOFException& e)
			{
				std::cout << e.GetError() << std::endl;
				return;
			}
		}

		void SkeletonData::ReadBoneChildren(Ptr<SkeletonBoneData> parent, File& skeletonFile)
		{
			String line = skeletonFile.GetLine();

			IOSStreamChar lineStream(line);

			String name;
			Float3 position;
			FQuaternion rotation;

			int children;

			ReadName(lineStream, name);
			ReadPosition(lineStream, position);
			ReadRotation(lineStream, rotation);

			lineStream >> children;

			UniquePtr<SkeletonBoneData> newParent = MakeUnique<SkeletonBoneData>(name, position, rotation);

			for (int i = 0; i < children; i++)
			{
				ReadBoneChildren(newParent.get(), skeletonFile);
			}

			parent->AddBone(move(newParent));
		}

		void SkeletonData::ReadName(IOSStreamChar& lineStream, String& name)
		{
			lineStream >> name;
		}

		void SkeletonData::ReadPosition(IOSStreamChar& lineStream, Float3& position)
		{
			lineStream >> position.X;
			lineStream >> position.Y;
			lineStream >> position.Z;
		}

		void SkeletonData::ReadRotation(IOSStreamChar& lineStream, FQuaternion& rotation)
		{
			lineStream >> rotation.X;
			lineStream >> rotation.Y;
			lineStream >> rotation.Z;
			lineStream >> rotation.W;
		}
	}
}