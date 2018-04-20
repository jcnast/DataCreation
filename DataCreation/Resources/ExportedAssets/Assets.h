
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
			const AssetType<Test>  = 1431655765;
		};
		const Test Tst;		struct ListTest
		{
		};
		const ListTest Lst;		struct Test2
		{
			const AssetType<Test2> Test 2 = 3616917144;
		};
		const Test2 Tst;		};
		const CustomAssets Cst;
	};
	const Assets Ast;
	}
