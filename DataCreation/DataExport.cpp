// DataCreation.cpp : Defines the entry point for the console application.
//

//#include "Data/CustomData/Exporting/Headers/DataCreation.h"
#include "Data/Rendering/Exporting/Headers/SceneConversion.h"

#include "Core/UnitTests/HashTesting.h"

int main()
{
	//DatabaseCreation("Data.db");
	SceneConversion::ConvertFilesForScene("Assets/NonConvertedFiles/MI/MI.obj", "MI");

	TestHashes();

    return 0;
}

