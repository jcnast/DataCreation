#include "Core/IO/Headers/IOUtils.h"

#include "Core/Debugging/Headers/Macros.h"

#include <direct.h>
#include <stdlib.h>
#include <stdio.h>

#include <Windows.h>
#include <stringapiset.h>

namespace Core
{
	namespace IO
	{
		File OpenFileI(FilePath file)
		{
			File openedFile(file, ios::in);

			openedFile.Open();

			MESSAGE(openedFile.FileStream.is_open(), "File <<" + file.GetFullPath() + ">> failed to open");

			return openedFile;
		}

		File OpenFileO(FilePath file)
		{
			File openedFile(file, ios::out);

			openedFile.Open();

			MESSAGE(openedFile.FileStream.is_open(), "File <<" + file.GetFullPath() + ">> failed to open");

			return openedFile;
		}

		// following https://msdn.microsoft.com/en-us/library/sf98bd4y.aspx
		String GetCWD()
		{
			char* buffer;
			bool success = false;

			// Get the current working directory:   
			if ((buffer = _getcwd(NULL, 0)) == NULL)
			{
				std::cout << "Failed to get CWD" << std::endl;
			}
			else
			{
				success = true;
			}

			String cwd = buffer + String("\\");

			if (success)
			{
				free(buffer);
			}
			
			std::cout << "CWD: " << cwd << std::endl;

			return cwd;
		}

		std::wstring StringToWString(const String& str)
		{
			int len;
			int slength = (int)str.length() + 1;
			len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), slength, 0, 0);
			wchar_t* buf = new wchar_t[len];
			MultiByteToWideChar(CP_ACP, 0, str.c_str(), slength, buf, len);
			std::wstring r(buf);
			delete[] buf;
			return r;
		}

		String WStringToString(const wchar_t* wstr)
		{
			std::ostringstream stm;

			while (*wstr != L'\0') {
				stm << std::use_facet< std::ctype<wchar_t> >(std::locale()).narrow(*wstr++, '?');
			}

			return stm.str();
		}
	}
}