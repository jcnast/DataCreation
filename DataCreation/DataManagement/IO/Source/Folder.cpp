#include "DataManagement/IO/Headers/Folder.h"

namespace Data
{
	namespace IO
	{
		CreateFolderResult CreateFolder(string path)
		{
			if (path.empty())
			{
				return CreateFolderResult::Error;
			}

			if (FolderExists(path))
			{
				return CreateFolderResult::AlreadyExists;
			}

			auto codePage = GetACP();
			int sz = MultiByteToWideChar(codePage, 0, &path[0], (int)path.size(), 0, 0);
			wstring wPath(sz, 0);
			MultiByteToWideChar(codePage, 0, &path[0], (int)path.size(), &wPath[0], sz);

			if (CreateDirectory(wPath.c_str(), nullptr))
			{
				return CreateFolderResult::Created;
			}
			return CreateFolderResult::Error;
		}

		bool FolderExists(string path)
		{
			auto fileAttributes = GetFileAttributesA(path.c_str());

			if (fileAttributes == INVALID_FILE_ATTRIBUTES)
			{
				return false;
			}
			else if (fileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				return true;
			}
			return false;
		}
	}
}