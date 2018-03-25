#pragma once

#include "Core/Headers/CoreDefs.h"

#include "Core/IO/Headers/Exception.h"

#include <ios>
#include <sstream>
#include <fstream>

using namespace std;

namespace Core
{
	namespace IO
	{
		// files
		template <typename charT>
		using IFStream = basic_ifstream<charT>;
		template <typename charT>
		using OFStream = basic_ofstream<charT>;
		template <typename charT>
		using FStream = basic_fstream<charT>;

		// strings
		template <typename charT>
		using ISStream = basic_ostringstream<charT>;
		template <typename charT>
		using OSStream = basic_istringstream<charT>;
		template <typename charT>
		using SStream = basic_stringstream<charT>;

		// specializations
		using IFStreamChar = IFStream<char>;
		using OFStreamChar = OFStream<char>;
		using IOFStreamChar = FStream<char>;

		using ISStreamChar = ISStream<char>;
		using OSStreamChar = OSStream<char>;
		using IOSStreamChar = SStream<char>;

		using OpenMode = ios::openmode;

		enum class Endian
		{
			Big,
			Little
		};

		struct FilePath
		{
			String File;
			String Path;

			String GetFullPath() const
			{
				return (File + Path);
			}
		};

		constexpr OpenMode DefaultPermissions = ios::in | ios::out;

		inline constexpr bool HasPermission(OpenMode userPermissions, OpenMode permission)
		{
			return ((userPermissions & permission) > 0);
		}
	}
}