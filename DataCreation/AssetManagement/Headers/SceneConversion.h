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
	string SceneStoragePath = "Assets/";
	string CurrentExportFolder;

	void ConvertFilesForScene(string importFileName, string exportFileName);

	void CreateFileForMesh(const aiScene* loadedScene, const aiMesh* mesh, uint32_t meshIndex, bool usesTexture);
	void CreateFileForMaterial(const aiMaterial* material, uint32_t materialIndex);

	// to be done later (or something like them):
	/*
	void CreateImageForMesh(const aiMesh* mesh, int imageIndex);
	void ConvertAnimationsToFile(const aiScene* scene, int animationIndex);
	*/

	bool CreateFolder(string path);
	ofstream OpenFile(string path, string file);
	void CloseFile(ofstream& openedFile, string path, string file);

	template <typename T>
	void WriteToFile(ofstream& openedFile, T arg)
	{
		openedFile << arg;
	}

	template <typename T, typename ...Ts>
	void WriteToFile(ofstream& openedFile, T arg, Ts ...args)
	{
		WriteToFile(openedFile, forward<T>(arg));
		WriteToFile(openedFile, forward<Ts>(args)...);
	}

	template <typename T>
	void WriteToFileCSV(ofstream& openedFile, T arg)
	{
		WriteToFile(openedFile, forward<T>(arg));;
	}

	template <typename T, typename ...Ts>
	void WriteToFileCSV(ofstream& openedFile, T arg, Ts ...args)
	{
		WriteToFile(openedFile, forward<T>(arg));
		WriteToFile(openedFile, ", ");
		WriteToFileCSV(openedFile, forward<Ts>(args)...);
	}

	template <typename ...Ts>
	void StartWritingToFile(string path, string file, ofstream& openedFile, Ts ...args)
	{
		cout << "Writing to <<" << path << file << ">>" << endl;
		WriteToFile(openedFile, forward<Ts>(args)...);
	}

	template <typename ...Ts>
	void StartWritingToFileCSV(string path, string file, ofstream& openedFile, Ts ...args)
	{
		cout << "Writing to <<" << path << file << ">>" << endl;
		WriteToFileCSV(openedFile, forward<Ts>(args)...);
	}
}