#include "AssetManagement\Headers\SceneConversion.h"

#include <stdio.h>
#include <vector>
// for folder creation
#include <Windows.h>

#include "ASSIMP\Compiler\cimport.h"
#include "ASSIMP\Compiler\scene.h"
#include "ASSIMP\Compiler\postprocess.h"
#include "ASSIMP\Compiler\material.h"

using namespace std;

namespace SceneConversion
{
	string CurrentExportFolder;

	void ConvertFilesForScene(string importFileName, string exportFolderName)
	{
		cout << "Converting files for <<" << importFileName << ">>, exporting to <<" << exportFolderName << ">>" << endl;
		// this process preset also INCLUDES the flag to make all faces based on triangles
		const aiScene* loadedScene = aiImportFile(importFileName.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);

		if (!loadedScene)
		{
			cout << "Could not load file <<" << importFileName << ">>: " << aiGetErrorString() << endl;
			return;
		}

		string folderPath = SceneStoragePath + exportFolderName;
		bool folderCreated = CreateFolder(folderPath);

		if (!folderCreated)
		{
			cout << "Could not create folder at " << folderPath << ">>" << endl;
			return;
		}
		else
		{
			CurrentExportFolder = folderPath;
		}

		int numberOfMeshes = loadedScene->mNumMeshes;

		for (int meshIndex = 0; meshIndex < numberOfMeshes; meshIndex++)
		{
			cout << "Creating file for mesh <<" << meshIndex << ">> out of <<" << meshIndex << ">>" << endl;
			CreateFileForMesh(loadedScene, loadedScene->mMeshes[meshIndex], meshIndex, false); // update this bool to be correct once we allow importing of this type of mesh
		}

		cout << "Releasing memory for loading scene <<" << importFileName << ">>" << endl;
		// needs to be done since assimp holds all of the memeory management for loading
		aiReleaseImport(loadedScene);
	}

	void CreateFileForMesh(const aiScene* loadedScene, const aiMesh* mesh, int meshIndex, bool usesTexture)
	{
		cout << "Creating file to hold mesh information for <<" << mesh->mName.data << ">>" << endl;

		vector<aiVector3D> positions;
		positions.reserve(mesh->mNumVertices);

		vector<aiVector3D> normals;
		normals.reserve(mesh->mNumVertices);

		cout << "Reading positions and normals from ASSIMP mesh data..." << endl;
		// get vertices from assimp into our format
		for (int vertexIndex = 0; vertexIndex < mesh->mNumVertices; vertexIndex++)
		{
			// get vertex and normal from mesh data
			positions.push_back(mesh->mVertices[vertexIndex]);
			normals.push_back(mesh->mNormals[vertexIndex]);
		}

		// get all indices out of assimp format int othe vector
		vector<uint32_t> faces;
		faces.reserve(mesh->mNumFaces * 3u); // 3 indices per triangle

		cout << "Reading [position/normal] indices used by each face..." << endl;
		for (uint32_t faceIndex = 0u; faceIndex < mesh->mNumFaces; faceIndex++)
		{
			// 3 indices for each face of the triangle
			faces.push_back(mesh->mFaces[faceIndex].mIndices[0u]);
			faces.push_back(mesh->mFaces[faceIndex].mIndices[1u]);
			faces.push_back(mesh->mFaces[faceIndex].mIndices[2u]);
		}

		string meshFileName = "MATERIAL_" + to_string(meshIndex);
		ofstream meshFile = OpenFile(CurrentExportFolder, meshFileName);

		cout << "Writing to <<" << CurrentExportFolder << meshFileName << ">>" << endl;
		meshFile << "positions\n";
		for (uint32_t positionIndex = 0u; positionIndex < positions.size(); positionIndex++)
		{
			WriteToFileCSV(meshFile, positions[positionIndex].x, positions[positionIndex].y, positions[positionIndex].z);
		}
		meshFile << "normals\n";
		for (uint32_t normalIndex = 0u; normalIndex < normals.size(); normalIndex++)
		{
			WriteToFileCSV(meshFile, normals[normalIndex].x, normals[normalIndex].y, normals[normalIndex].z);
		}
		meshFile << "indices\n";
		for (uint32_t faceIndex = 0u; faceIndex << faces.size(); faceIndex += 3) // += 3 because 3 vertices to a face (triangles)
		{
			WriteToFileCSV(meshFile, faces[faceIndex], faces[faceIndex + 1], faces[faceIndex + 2]);
		}

		CloseFile(meshFile, CurrentExportFolder, meshFileName);

		// create file for material
		CreateFileForMaterial(loadedScene->mMaterials[mesh->mMaterialIndex], mesh->mMaterialIndex);
	}

	void CreateFileForMaterial(const aiMaterial* material, int materialIndex)
	{
		cout << "Creating file to hold material information for index <<" << materialIndex << ">> in file <<MATERIAL_" << materialIndex << ">>" << endl;
		// material values
		aiColor4D specularColor;
		aiColor4D diffuseColor;
		aiColor4D ambientColot;
		float shininess;

		cout << "Getting material information from assimp..." << endl;
		// get values from assimp material
		aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &specularColor);
		aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuseColor);
		aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &ambientColot);
		aiGetMaterialFloat(material, AI_MATKEY_SHININESS, &shininess);

		// store values in file
		string materialFileName = "MATERIAL_" + to_string(materialIndex);
		ofstream materialFile = OpenFile(CurrentExportFolder, materialFileName);
		StartWritingToFile(CurrentExportFolder, materialFileName, materialFile, "spec ", specularColor.r, specularColor.g, specularColor.b, specularColor.a);
		CloseFile(materialFile, CurrentExportFolder, materialFileName);
	}

	bool CreateFolder(string path)
	{
		const wchar_t* wcharPath = wstring(path.begin(), path.end()).c_str();
		return CreateDirectory(wcharPath, nullptr);
	}

	ofstream OpenFile(string path, string file)
	{
		cout << "Opening file <<" << path << file << ">>" << endl;
		ofstream openedFile;
		openedFile.open(path + file);
	}

	void CloseFile(ofstream& openedFile, string path, string file)
	{
		cout << "Closing file <<" << path << file << ">>" << endl;
		openedFile.close();
	}
}