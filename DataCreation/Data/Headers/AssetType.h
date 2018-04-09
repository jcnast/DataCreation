#pragma once

#include "Core/Headers/Hash.h"

#include "Data/Headers/AssetExceptions.h"

using namespace Core;

namespace Data
{
	template <typename T>
	struct AssetType
	{
		Hash TypeName;

		String GetPath() const
		{
			return T::GetPath();
		}

		String GetFileType() const
		{
			return T::GetPath();
		}
	};
}