#include "Core/IO/Headers/File.h"

#include "Core/Debugging/Headers/Macros.h"

namespace Core
{
	namespace IO
	{
		File::File(FilePath path, OpenMode permissions, Endian endian)
			: Path(path), FilePermissions(permissions), FileEndian(endian), CursorPosition(0), FileLength(0)
		{

		}

		String File::GetFullPath()
		{
			return (Path.GetFullPath());
		}

		void File::SetPermissions(OpenMode permissions)
		{
			Close();
			Open();
		}

		void File::Open()
		{
			cout << "Opening file <<" << GetFullPath() << ">>" << endl;

			FileStream.open(GetFullPath(), FilePermissions);

			if (FileStream.is_open())
			{
				FileStream.seekg(0, FileStream.end);
				FileLength = uint(FileStream.tellg());

				FileStream.seekg(0, FileStream.beg);
				CursorPosition = uint(FileStream.tellg());
			}
			else
			{
				cout << "File could not open, attempting to create and then reopening" << endl;

				if (Create())
				{
					Open();
				}
				else
				{
					throw IOException("File <" + GetFullPath() + "> was unable to be opened");
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
		
		bool File::GoToPosition(uint position)
		{
			if (position > FileLength)
			{
				return false;
			}

			FileStream.seekg(position, FileStream.beg);
			CursorPosition = uint(FileStream.tellg());

			return true;
		}

		uint File::GetPosition()
		{
			return CursorPosition;
		}

		bool File::MoveToNextLine()
		{
			if (HasPermission(FilePermissions, ios::in) && CursorPosition < FileLength)
			{
				FileStream.ignore(unsigned(-1), '\n');
				CursorPosition = uint(FileStream.tellg());

				return true;
			}

			return false;
		}

		bool File::CreateNewLine()
		{
			return Write('\n');
		}

		String File::GetLine()
		{			
			if (HasPermission(FilePermissions, ios::in) && CursorPosition < FileLength)
			{
				String Line;
				if (!std::getline(FileStream, Line))
				{
					throw EOFException("End of <" + GetFullPath() + "> reached");
				}

				CursorPosition = uint(FileStream.tellg());

				return Line;
			}
			throw IOException("Can't get line for this file - incorrect permissions or invalid position");
		}
	}
}