#pragma once

#include "IODefs.h"
#include "File.h"

namespace Core
{
	namespace IO
	{
		File OpenFileIO(FilePath file);
		File OpenFileI(FilePath file);
		File OpenFileO(FilePath file);

		String GetCWD();
	}
}