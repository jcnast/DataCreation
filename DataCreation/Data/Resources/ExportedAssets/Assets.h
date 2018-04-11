#pragma once

#include "Data/Headers/AssetType.h"
#include "Data/Headers/AssetName.h"

#include "CustomAssets.h"
#include "MaterialAssets.h"
#include "MeshAssets.h"

namespace Data
{
	/*
		This file should be auto-generated with each 'code-referencable' piece of data automatically constructed as an AssetName in the same way each AssetType is
	*/
	struct Assets
	{
		struct CustomAssets
		{
			struct Samples
			{
				const AssetName<SampleData> SpecificAsset /*= Specific Asset Hash*/;
			};
			const Samples Smp;
		};
		const CustomAssets Dat;

		struct Materials
		{
			const AssetName<Rendering::MaterialData> SpecificMaterial /*= Specific Material Hash*/;
		};
		const Materials Mat;

		struct Meshes
		{
			const AssetName<Rendering::MeshData> SpecificMesh /*= Specific Mesh Hash*/;
		};
		const Meshes Msh;
	};
	const Assets Ast;
}