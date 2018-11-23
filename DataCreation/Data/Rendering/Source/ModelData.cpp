#include "Data/Rendering/Headers/ModelData.h"

#include "Core/IO/Headers/IOUtils.h"

#include "Core/Debugging/Headers/Macros.h"

using namespace Core;
using namespace Core::IO;
using namespace Core::Math;

namespace Data
{
	namespace Rendering
	{
		ModelData::ModelData(String fileName)
		{
			File modelFile = OpenFileI(FilePath{ String("PATH TO FILE"), fileName });

			MESSAGE(modelFile.FileStream.is_open(), "FAILED TO READ FILE <<" + fileName + ">>");

			try
			{
				String line = modelFile.GetLine();

				IOSStreamChar lineStream(line);
				
				lineStream >> Material.Name.H;
				lineStream >> Mesh.Name.H;
				lineStream >> Skeleton.Name.H;
				lineStream >> Texture.Name.H;
			}
			catch (EOFException& e)
			{
				std::cout << e.GetError() << std::endl;
			}

			modelFile.Close();
		}
	}
}