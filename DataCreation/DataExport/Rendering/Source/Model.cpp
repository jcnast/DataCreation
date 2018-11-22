#pragma once

#include "DataExport/Rendering/Headers/MeshExport.h"

#include "Core/Headers/ListDefs.h"
#include "Core/Headers/Hash.h"

#include "Core/Debugging/Headers/Macros.h"

#include "Core/IO/Headers/File.h"
#include "Core/IO/Headers/Folder.h"
#include "Core/IO/Headers/IOUtils.h"

#include "Core/Math/Headers/Vector2.h"
#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/Vector4.h"

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
		void CreateFileForModel(Ptr<File> directAssets, Ptr<const aiScene> scene, String name)
		{
			

			FilePath meshFilePath = FilePath{ GetCWD() + "/Resources/ExportedAssets/Models/", ToString(HashValue(name)) + ".mdl" };
			File meshFile = File(meshFilePath, ios::out);
			meshFile.Open();

			

			meshFile.Close();
		}
	}
}
