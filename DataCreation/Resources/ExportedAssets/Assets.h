
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
		tempalte <>		struct CustomAssets
		{
		tempalte <>		struct Test
		{
			const AssetName<Test>  = 1431655765;
		};
		const Test Tst;
		tempalte <>		struct ListTest
		{
		};
		const ListTest Lst;
		tempalte <>		struct Test2
		{
			const AssetName<Test2> Test 2 = 3616917144;
		};
		const Test2 Tst;
		tempalte <>		struct Models
		{
			const AssetName<Models> MI = 1238742485;
			const AssetName<Models> Wolf = 1631375646;
			const AssetName<Models> Woman = 3273357991;
		};
		const Models Mdl;
		};
		const CustomAssets Cst;
		struct StaticModels
		{
		};
		const StaticModels smdl;
		struct AnimatedModels
		{
		};
		const AnimatedModels amdl;
		struct Meshes
		{
		};
		const Meshes msh;
		struct Materials
		{
		};
		const Materials mat;
		struct Skeletons
		{
		};
		const Skeletons skl;
		struct SkeletonAnimations
		{
		};
		const SkeletonAnimations sanim;

	};
	const Assets Ast;
	}
