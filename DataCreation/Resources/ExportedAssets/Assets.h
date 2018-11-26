
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
		struct Models
		{
			const AssetName<Models> MI = 1238742485;
			const AssetName<Models> Wolf = 1631375646;
			const AssetName<Models> Woman = 3273357991;
		};
		const Models Mdl;
		};
		const CustomAssets Cst;
		struct Models
		{
		};
		const Models Mdl;
		struct Meshes
		{
		};
		const Meshes Msh;
		struct Materials
		{
		};
		const Materials Mat;
		struct Skeletons
		{
		};
		const Skeletons Skl;
		struct SkeletonAnimations
		{
		};
		const SkeletonAnimations SAnim;

	};
	const Assets Ast;
	}
