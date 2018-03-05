#include "DataManagement/IO/Headers/File.h"

namespace Data
{
	namespace IO
	{
		File::File(string path, string fileName, ios::openmode permissions, Endian endian)
			: FilePath(path), FileName(fileName), FilePermissions(permissions), FileEndian(endian), CursorPosition(0), FileLength(0)
		{

		}

		string File::GetFullPath()
		{
			return (FilePath + "/" + FileName);
		}

		void File::Open()
		{
			cout << "Opening file <<" << GetFullPath() << ">>" << endl;

			FileStream.open(GetFullPath(), FilePermissions);

			if (FileStream.is_open())
			{
				FileStream.seekg(0, FileStream.end);
				FileLength = FileStream.tellg();

				FileStream.seekg(0, FileStream.beg);
				CursorPosition = FileStream.tellg();
			}
			else
			{
				cout << "File could not open, attempting to create and then reopening" << endl;

				if (Create())
				{
					Open();
				}
			}
		}

		void File::Close()
		{
			cout << "Closing file <<" << GetFullPath() << ">>" << endl;

			FileStream.close();
		}

		bool File::Create()
		{
			FileStream.open(GetFullPath(), ios::out);

			bool created = FileStream.is_open();

			FileStream.close();

			return created;
		}

		bool File::Delete()
		{
			return (remove(GetFullPath().c_str()) != 0);
		}

		void File::Clear()
		{
			Close();

			FileStream.open(GetFullPath(), ios::trunc); // reopen and clear
			FileStream.close();

			Open();
		}

		bool File::MoveToNextLine()
		{
			if (HasPermission(FilePermissions, ios::in) && CursorPosition < FileLength)
			{
				FileStream.ignore(unsigned(-1), '\n');
				return true;
			}

			return false;
		}

		bool File::CreateNewLine()
		{
			return Write('\n');
		}
	}
}