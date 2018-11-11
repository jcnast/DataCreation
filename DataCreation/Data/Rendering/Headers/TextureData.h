#pragma once

#include "Core/Headers/CoreDefs.h"
#include "Core/Math/Headers/Vector2.h"

using namespace Core;
using namespace Core::Math;

namespace Data
{
	namespace Rendering
	{
		struct TextureData
		{
			Float2 Size;
			String ImageFile;

			TextureData() = delete;

			TextureData(String file);
		};
	}
}