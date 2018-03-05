#pragma once

#include <fstream>
#include <string>
#include <iostream>

using namespace std;

struct aiScene;
struct aiMesh;
struct aiMaterial;

namespace SceneConversion
{
	static string SceneStoragePath = "C:/Users/Jagger/Desktop/Coding/VisualStudios/DataCreation/DataCreation/Assets/ExportedAssets/";
	static string CurrentExportFolder = "";

	void ConvertFilesForScene(string importFileName, string exportFileName);

	void CreateFileForMesh(const aiScene* loadedScene, const aiMesh* mesh, uint32_t meshIndex, bool usesTexture);
	void CreateFileForMaterial(const aiMaterial* material, uint32_t materialIndex);

	// to be done later (or something like them):
	/*
	void CreateImageForMesh(const aiMesh* mesh, int imageIndex);
	void ConvertAnimationsToFile(const aiScene* scene, int animationIndex);
	*/
}
