#pragma once

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/ListDefs.h"

#include "Data/Headers/AssetName.h"

#include "Data/Rendering/Headers/MaterialData.h"
#include "Data/Rendering/Headers/MeshData.h"
#include "Data/Rendering/Headers/SkeletonData.h"
#include "Data/Rendering/Headers/TextureData.h"

using namespace Core;

namespace Data
{
	namespace Rendering
	{
		// holds the information about the mesh of a 3D object
		struct ModelData
		{
			AssetName<MaterialData> Material;
			AssetName<MeshData> Mesh;
			AssetName<SkeletonData> Skeleton;
			AssetName<TextureData> Texture;

			ModelData() = default;
			ModelData(String fileName);
		};
	}
}