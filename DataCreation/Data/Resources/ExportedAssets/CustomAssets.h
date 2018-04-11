#pragma once

#include "Data/Headers/AssetType.h"

namespace Data
{
	struct SampleData
	{
		/*
		Actual data setup
		*/
	};

	struct AssetType<SampleData>
	{
		Hash ClassHash() const
		{
			return Core::HashValue("SampleAsset");
		}

		String GetPath() const
		{
			return "CustomAssets/SampleAsset/";
		}

		String GetFileType() const
		{
			return ".smp";
		}
	};
}