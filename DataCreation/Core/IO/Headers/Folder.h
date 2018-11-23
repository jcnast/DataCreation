#pragma once

#include "File.h"
#include "IODefs.h"

#include "Core/Headers/ListDefs.h"

namespace Core
{
	namespace IO
	{
		enum class CreateFolderResult
		{
			AlreadyExists,
			Created,
			Error
		};

		CreateFolderResult CreateFolder(String path);
		bool FolderExists(String path);

		List<String> AllFilesInFolder(String path, bool recursive = false);

		// Functions to be done later:

		/*

		void DeleteFolder(string path
		void Clearfolder(string path);

		*/
	}
}