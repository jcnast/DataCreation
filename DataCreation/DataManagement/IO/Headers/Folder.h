#pragma once

#include "IODefs.h"

using namespace std;

namespace Data
{
	namespace IO
	{
		enum class CreateFolderResult
		{
			AlreadyExists,
			Created,
			Error
		};

		CreateFolderResult CreateFolder(string path);
		bool FolderExists(string path);

		// Functions to be done later:

		/*

		void DeleteFolder(string path
		void Clearfolder(string path);

		*/
	}
}