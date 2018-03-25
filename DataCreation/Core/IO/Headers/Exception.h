#pragma once

#include "Core/Headers/Exception.h"

namespace Core
{
	namespace IO
	{
		struct IOException : Exception
		{
			using Exception::Exception;
		};
	}
}