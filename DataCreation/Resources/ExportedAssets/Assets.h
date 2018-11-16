
#pragma once

#include "Data/Headers/AssetType.h"
#include "Data/Headers/AssetName.h"

#include "CustomAssets.h"
#include "MaterialAssets.h"
#include "MeshAssets.h"

namespace Data
{
	/*
		This file has been auto-generated

		DO NOT CHANGE
	*/
	struct Assets
	{
		struct CustomAssets
		{
		struct Test
		{
			const AssetName<Test>  = 1431655765;
		};
		const Test Tst;
		struct ListTest
		{
		};
		const ListTest Lst;
		struct Test2
		{
			const AssetName<Test2> Test 2 = 3616917144;
		};
		const Test2 Tst;
		};
		const CustomAssets Cst;
		struct Meshes
		{
			const AssetName<Rendering::MeshData> MI = 1238742485;
		};
		const Meshes Msh;
		struct Materials
		{
			const AssetName<Rendering::MaterialData> MI = 1238742485;
		};
		const Materials Mat;

	};
	const Assets Ast;
	}
