#pragma once

#include "IODefs.h"
#include "File.h"

namespace Core
{
	namespace IO
	{
		File OpenFileI(FilePath file);
		File OpenFileO(FilePath file);

		String GetCWD();

		std::wstring StringToWString(const String& str);
		String WStringToString(const wchar_t* wstr);
	}
}