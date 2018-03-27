// DataCreation.cpp : Defines the entry point for the console application.
//

#include "DataManagement/Headers/FileCreation.h"
#include "AssetManagement/Headers\SceneConversion.h"

#include "DataManagement/Headers/HashTesting.h"

int main()
{
	DatabaseCreation("Data.db");
	SceneConversion::ConvertFilesForScene("Assets/NonConvertedFiles/MI/MI.obj", "MI");

	TestHashes();

    return 0;
}

