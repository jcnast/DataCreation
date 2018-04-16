#include "DataExport/CustomData/Headers/DataExportDefs.h"

namespace Data
{
	namespace DataExport
	{
		String DataType::GetDefinition()
		{
			String definition = "struct " + Name + "\n";
			definition += "{\n";
			for (auto& prop : Properties)
			{
				if (prop != nullptr)
				{
					definition += "\t" + prop->GetLine() + "\n";
				}
			}
			definition += "}\n";
			definition += "\n";

			return definition;
		}

		String DataType::GetMetaTypeDefinition()
		{
			String definition = "struct AssetType<" + Name + ">\n";
			definition += "{\n";
			definition += "\tHash ClassHash() const\n";
			definition += "\t{\n";
			definition += "\t\treturn Core::HashValue(\"" + Name + "\");\n";
			definition += "\t}\n";
			definition += "\n";
			definition += "\tString GetPath() const\n";
			definition += "\t{\n";
			definition += "\t\treturn \"CustomAssets/" + Name + "\"/;\n";
			definition += "\t}\n";
			definition += "\n";
			definition += "\tString GetFileType() const\n";
			definition += "\t{\n";
			definition += "\t\treturn \"." + Acronym + "\";\n";
			definition += "\t}\n";
			definition += "};\n";

			return definition;
		}
	}
}