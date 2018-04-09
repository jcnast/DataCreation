#pragma once

#include "SQLite/sqlite3.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

struct StructAttribute
{
	std::string Title;
	std::string Type;
	bool List;
	bool PrimaryKey;
	bool ForeignKey;
};

std::string StructName;
std::vector<StructAttribute> Attributes;

bool CharIsNotAllowedInAttribute(char c)
{

}

std::string GetCPPEquivalentOfSQLite(std::string type)
{

}

void ParseSQLite(char* argv)
{

}

void CreateConstructor(std::ofstream* headerFile)
{

}

void CreateDestructor(std::ofstream* headerFile)
{

}

int CreateAttributes(void* file, int argc, char** argv, char** azColName)
{

}

int CreateStruct(void* db, int argc, char** argv, char** azColName)
{

}

void DatabaseCreation(std::string dataBaseFile)
{

}