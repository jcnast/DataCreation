#include "Data/Rendering/Headers/TextureData.h"

#include "Core/IO/Headers/IOUtils.h"

#include "Core/Debugging/Headers/Macros.h"

using namespace Core;
using namespace Core::IO;

namespace Data
{
	namespace Rendering
	{
		TextureData::TextureData(String fileName)
		{
			File meshFile = OpenFileI(FilePath{ String("PATH TO FILE"), fileName });

			MESSAGE(meshFile.FileStream.is_open(), "FAILED TO READ FILE <<" + fileName + ">>");

			try
			{
				String line = meshFile.GetLine();

				IOSStreamChar lineStream(line);

				lineStream >> Size.X;
				lineStream >> Size.Y;

				lineStream >> ImageFile;
			}
			catch (EOFException& e)
			{
				// this is how this should end (for now at least)
				std::cout << e.GetError() << std::endl;
			}
		}
	}
}