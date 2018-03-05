#pragma once

#include <fstream>
#include <string>
#include <iostream>

#include <Windows.h>

using namespace std;

namespace Data
{
	namespace IO
	{
		enum class Endian
		{
			Big,
			Little
		};

		constexpr ios::openmode DefaultPermissions = ios::in | ios::out;

		inline constexpr bool HasPermission(ios::openmode userPermissions, ios::openmode permission)
		{
			return ((userPermissions & permission) > 0);
		}
	}
}