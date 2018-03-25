#pragma once

#include "IODefs.h"

namespace Core
{
	namespace IO
	{
		struct File
		{
			FilePath Path;

			OpenMode FilePermissions;
			Endian FileEndian;

			uint FileLength;
			uint CursorPosition;
			/*
				should also have a BIT cursor position, with the current CursorPosition referring to the byte position, so that we can read out the exact number of
				bits for whatever data type is required by using sizeof() to get bit count, and handling the EXACT positioning ourselves.
			*/

			IOFStreamChar FileStream;

			File(FilePath path, OpenMode permissions = DefaultPermissions, Endian endian = Endian::Big);

			String GetFullPath();

			void Open();
			void Close();

			bool Create();
			bool Delete();
			void Clear();

			bool MoveToNextLine();
			bool CreateNewLine();

			template <typename T>
			bool Read(T&& target)
			{
				if (HasPermission(FilePermissions, ios::in) && CursorPosition < FileLength)
				{
					ReadToTarget(target);

					return true;
				}

				return false;
			}

			template <typename T, typename ...Ts>
			bool Read(T&& target, Ts&& ...args)
			{
				if (Read(target))
				{
					return Read(forward<Ts>(args)...);
				}
				return false;
			}

			template <typename T>
			bool Write(T&& source)
			{
				if (HasPermission(FilePermissions, ios::out))
				{
					FileStream << source;
					CursorPosition = FileStream.tellg();

					return true;
				}

				return false;
			}

			template <typename T, typename ...Ts>
			bool Write(T&& source, Ts&& ...args)
			{
				if (Write(source))
				{
					Write(" ");
					return Write(forward<Ts>(args)...);
				}
				return false;
			}

		private:
			template <typename T>
			void ReadToTarget(T&& target)
			{
				if (HasPermission(FilePermissions, ios::binary))
				{
					throw exception;
					//ReadBinaryToTarget(target);
				}
				else
				{
					FileStream >> target;
					CursorPosition = FileStream.tellg();
				}
			}

			void ReadBinaryToTarget(char* target, int numBytes)
			{
				// need to figure out handling for things like bools which are on bit instead of a byte (maybe doesn't matter if we have the same data structures and just do raw casting?)
				if (FileEndian == Endian::Big)
				{

				}
				else
				{

				}
			}

			template <typename T>
			void WriteFromSource(T&& source)
			{
				if (HasPermission(FilePermissions, ios::binary))
				{
					throw exception;
					//WriteBinaryFromSource(source);
				}
				else
				{
					source >> FileStream;
					CursorPosition = FileStream.tellg();

					FileStream.seekg(0, FileStream.end);
					FileLength = FileStream.tellg();

					FileStream.seekg(CursorPosition, FileStream.beg);
				}
			}

			void WriteBinaryFromSource(char* source, int numBytes)
			{
				// need to figure out handling for things like bools which are on bit instead of a byte (maybe doesn't matter if we have the same data structures and just do raw casting?)
				if (FileEndian == Endian::Big)
				{

				}
				else
				{

				}
			}
		};
	}
}