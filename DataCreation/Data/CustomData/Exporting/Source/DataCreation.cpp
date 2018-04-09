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
	std::vector<char> DisallowedChars = { '"', '(', ')', '[', ']', '{', '}' };

	for (auto& disallowedChar : DisallowedChars)
	{
		if (c == disallowedChar)
		{
			return true;
		}
	}

	return false;
}

std::string GetCPPEquivalentOfSQLite(std::string type)
{
	if (type == "BIGINT" || type == "DATE" || type == "DATETIME")
	{
		return "uint32_t";
	}
	else if (type == "BLOB" || type == "STRING" || type == "TEXT" || type == "VARCHAR")
	{
		return "string";
	}
	else if (type == "BOOLEAN")
	{
		return "bool";
	}
	else if (type == "CHAR")
	{
		return "char";
	}
	else if (type == "DECIMAL" || type == "REAL")
	{
		return "float";
	}
	else if (type == "DOUBLE")
	{
		return "double";
	}
	else if (type == "INTEGER" || type == "INT")
	{
		return "int";
	}
	else if (type == "NUMERIC")
	{
		return "<ERROR: ambiguous>";
	}
	else // || type == "NONE"
	{
		return "<ERROR: nothing specified>";
	}
}

void ParseSQLite(char* argv)
{
	size_t position = 0;
	std::string sql = argv;

	std::string subString;
	std::stringstream subStringStream;

	{ // first pass to get the SQL past the create table call
		position = sql.find("(");
		sql.erase(0, position + 1); // plus length of delimeter
	}

	while (true)
	{
		StructAttribute newAttribute;

		position = sql.find(",");

		subString = sql.substr(0, position);
		subStringStream.str(subString);

		{
			subStringStream >> newAttribute.Title;
			subStringStream >> newAttribute.Type;

			if (newAttribute.Title.find("List") != std::string::npos)
			{
				newAttribute.List = true;
			}
			else
			{
				newAttribute.List = false;
			}

			size_t subPosition = 0;

			if ((subPosition = subString.find("PRIMARY KEY")) != std::string::npos)
			{
				subString.erase(0, subPosition + std::string("PRIMARY KEY").length());

				newAttribute.PrimaryKey = true;
			}
			else
			{
				newAttribute.PrimaryKey = false;
			}
			if ((subPosition = subString.find("REFERENCES")) != std::string::npos)
			{
				subString.erase(0, subPosition + std::string("REFERENCES").length());

				newAttribute.ForeignKey = true;

				subStringStream.str(subString);

				subStringStream >> newAttribute.Type;
				// remove unwanted characters
				newAttribute.Type.erase(std::remove_if(newAttribute.Type.begin(), newAttribute.Type.end(), CharIsNotAllowedInAttribute), newAttribute.Type.end());
			}
			else
			{
				newAttribute.ForeignKey = false;

				// remove unwanted characters
				newAttribute.Type.erase(std::remove_if(newAttribute.Type.begin(), newAttribute.Type.end(), CharIsNotAllowedInAttribute), newAttribute.Type.end());
				newAttribute.Type = GetCPPEquivalentOfSQLite(newAttribute.Type);
			}
			// remove unwatned characters
			newAttribute.Title.erase(std::remove_if(newAttribute.Title.begin(), newAttribute.Title.end(), CharIsNotAllowedInAttribute), newAttribute.Title.end());

			// add in the declaraction of regular data types
			Attributes.push_back(newAttribute);
		}

		sql.erase(0, position + 1); // plus length of delimeter

		if (position == std::string::npos)
		{
			break;
		}
	}
}

void CreateConstructor(std::ofstream* headerFile)
{
	*headerFile << "\t" << StructName << "(DataManager& dataManager";

	for (auto& attribute : Attributes)
	{
		if (attribute.PrimaryKey)
		{
			*headerFile << ", " << attribute.Type << " " << attribute.Title;
		}
	}

	*headerFile << ")\n\t{\n";

	*headerFile << "\t\t";
	*headerFile << "dataManager.GetData(";

	bool first = true;
	for (auto& attribute : Attributes)
	{
		if (attribute.PrimaryKey)
		{
			*headerFile << (first ? "" : ", ") << attribute.Title;
		}
	}

	*headerFile << ");\n\t}";
}

void CreateDestructor(std::ofstream* headerFile)
{
	*headerFile << "\t~" << StructName << "();\n";
}

int CreateAttributes(void* file, int argc, char** argv, char** azColName)
{
	std::ofstream* headerFile = static_cast<std::ofstream*>(file);

	// create attributes
	for (int i = 0; i < argc; i++)
	{
		//*headerFile << (argv[i] ? argv[i] : "NULL") << "\n"; // to see the raw SQL string
		ParseSQLite(argv[i]);
	}

	for (auto& attribute : Attributes)
	{
		*headerFile << "\t" << (attribute.List ? "List<" : "") << attribute.Type << (attribute.List ? ">" : "") << " " << attribute.Title << ";\n";
	}

	return 0;
}

int CreateStruct(void* db, int argc, char** argv, char** azColName)
{
	{ // reset globals
		StructName = "";
		Attributes.clear();
	}

	sqlite3* openedDB = static_cast<sqlite3*>(db);
	if (argv[0])
	{
		std::string fileName = "Database/";

		StructName = argv[0];

		fileName += StructName + ".h";

		{ // add in file to the master include
			std::ofstream includeFile;
			includeFile.open("Data/DataStructs.h", std::ios::app);

			includeFile << "#include \"" << StructName << ".h\"\n";

			includeFile.close();
		}

		std::ofstream headerFile;
		headerFile.open(fileName);

		headerFile << "// Automatically created struct from database.\n";
		headerFile << "/*\n";
		headerFile << "  DO NOT MODIFY!\n";
		headerFile << "*/\n";
		headerFile << "\n";
		headerFile << "struct " << StructName << "\n";
		headerFile << "{\n";

		{ // create struct attributes
		  // sql from: https://stackoverflow.com/questions/2418527/sql-server-query-to-get-the-list-of-columns-in-a-table-along-with-data-types-no
			std::string sql = "SELECT sql FROM sqlite_master WHERE name = '" + StructName + "'";

			char* errorMessage = 0;
			int rc;
			rc = sqlite3_exec(openedDB, sql.c_str(), CreateAttributes, &headerFile, &errorMessage);

			if (rc != SQLITE_OK)
			{
				std::cout << "Unable to read in each data type and name from database: %s\n" << errorMessage << std::endl;
				sqlite3_free(errorMessage);
			}
			else
			{
				std::cout << "Success in reading each data type and name from database\n" << std::endl;
			}
		}

		{ // create struct methods
			headerFile << "\n";
			CreateConstructor(&headerFile);
			headerFile << "\n";
			CreateDestructor(&headerFile);
		}

		headerFile << "};\n";

		headerFile.close();
	}
	else
	{
		std::cout << "Could not create struct - NULL given as name" << std::endl;
	}

	return 0;
}

void DatabaseCreation(std::string dataBaseFile)
{
	{ // clear out file and write in default stuff
		std::ofstream includeFile;
		includeFile.open("Data/DataStructs.h");

		includeFile << "#pragma once\n\n";

		includeFile.close();
	}

	sqlite3* db;
	char* errorMessage = 0;
	int rc;
	char* sql;

	std::string dataBasePath = "Data/";
	dataBasePath += dataBaseFile;

	rc = sqlite3_open(dataBasePath.c_str(), &db);

	if (rc)
	{
		std::cout << "failed to open db: " << sqlite3_errmsg(db) << std::endl;
	}
	else
	{
		std::cout << "opened db" << std::endl;
	}

	sql = "SELECT name FROM sqlite_master WHERE type='table'";

	rc = sqlite3_exec(db, sql, CreateStruct, db, &errorMessage);

	if (rc != SQLITE_OK)
	{
		std::cout << "Unable to read each table from database: %s\n" << errorMessage << std::endl;
		sqlite3_free(errorMessage);
	}
	else
	{
		std::cout << "Success in reading each table from database\n" << std::endl;
	}

	sqlite3_close(db);
}