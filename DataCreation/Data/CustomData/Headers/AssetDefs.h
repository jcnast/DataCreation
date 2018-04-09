#pragma once

#include "Data/Headers/AssetType.h"

namespace Data
{
	namespace CustomData
	{
		struct DataType : AssetType
		{
			String GetPath() const override
			{
				return "Resources/ExportedAssets/CustomData/";
			}

			String GetFileType() const override
			{
				return ".dat";
			}
		};
	}
}