#include "DataExport/CustomData/Headers/DataExportUtils.h"

#include "DataExport/Headers/ExportException.h"

namespace Data
{
	namespace DataExport
	{
		UniquePtr<DataType> CreateType(String sql)
		{
			auto typeName = TableName(sql);
			UniquePtr<DataType> NewType = MakeUnique<DataType>(typeName, Acronym(typeName));

			auto sqlCommands = sql.substr(sql.find("(") + 1, sql.find(")"));

			while (true)
			{
				auto nextCommand = sqlCommands.find(",");
				auto sqlCommand = sqlCommands.substr(0, nextCommand);

				CreateProperty(sqlCommand);

				sqlCommands = ClipLeadingWhitespace(sqlCommands.substr(nextCommand + 1));
				if (sqlCommands.length() == 0)
				{
					break;
				}
			}
		}

		UniquePtr<DataProperty> CreateProperty(String sqlColumn)
		{
			String type = TypeName(sqlColumn);
			String name = FieldName(sqlColumn);

			if (IsPrimaryKey(sqlColumn))
			{
				// this is the name of the file
			}

			UniquePtr<DataProperty> newProperty;

			if (IsList(sqlColumn))
			{
				newProperty = MakeUnique<DataPropertyList>(type, name);
			}
			else if (IsForeignKey(sqlColumn))
			{
				newProperty = MakeUnique<DataPropertyData>(type, name);
			}
			else
			{
				newProperty = MakeUnique<DataProperty>(type, name);
			}

			return move(newProperty);
		}

		String TableName(String sql)
		{
			String header = "CREATE TABLE";
			auto index = sql.find(header);

			auto remaining = sql.substr(index + header.length());
			remaining = ClipLeadingWhitespace(remaining);

			auto name = remaining.substr(0, remaining.find(" "));

			return name;
		}

		String Acronym(String tableName)
		{
			List<char> vowels = { 'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U' };

			String acronym;

			int index = 0;
			while (acronym.length() < 3)
			{
				if (!InList(vowels, tableName[index]))
				{
					acronym += tableName[index];
				}

				index++;
			}

			return acronym;
		}

		String FieldName(String sqlColumn)
		{
			return sqlColumn.substr(0, sqlColumn.find(" "));
		}

		String TypeName(String sqlColumn)
		{
			auto firstSpace = sqlColumn.find(" ") + 1;
			auto secondSpace = sqlColumn.find(" ", firstSpace);
			auto sqlType = sqlColumn.substr(firstSpace, secondSpace);

			if (sqlType == "BOOLEAN")
			{
				return "bool";
			}
			else if (sqlType == "INT")
			{
				return "int";
			}
			else if (sqlType == "STRING")
			{
				return "String";
			}
			else if (sqlType == "FLOAT")
			{
				return "float";
			}

			throw CustomExportException("Uknown sql type field <" + sqlType + ">");
		}

		bool IsPrimaryKey(String sqlColumn)
		{
			return (sqlColumn.find("PRIMARY KEY") < sqlColumn.length());
		}

		bool IsForeignKey(String sqlColumn)
		{
			return (sqlColumn.find("REFERENCES") < sqlColumn.length());
		}

		String GetForeignKeyType(String sqlColumn)
		{
			if (IsForeignKey(sqlColumn))
			{
				auto start = sqlColumn.find("REFERENCES");
				auto remaining = ClipLeadingWhitespace(sqlColumn.substr(start));

				return remaining.substr(0, remaining.find(" "));
			}

			throw CustomExportException("Foreign key type requested for non foreign key type! <" + sqlColumn + ">");
		}

		bool IsList(String sqlColumn)
		{
			return ("List" == sqlColumn.substr(0, 4));
		}

		bool IsExported(String sqlColumn)
		{
			return ("ExportDirectly" == sqlColumn.substr(0, 14));
		}

		String ClipLeadingWhitespace(String str)
		{
			auto index = str.find(" ");

			if (index == 0)
			{
				return str;
			}

			return str.substr(1);
		}
	}
}