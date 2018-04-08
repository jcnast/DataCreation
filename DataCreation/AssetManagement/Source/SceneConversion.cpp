#include "AssetManagement\Headers\SceneConversion.h"

#include <stdio.h>
#include <vector>
// for folder creation
#include <Windows.h>

#include "Core/IO/Headers/File.h"
#include "Core/IO/Headers/Folder.h"

#include "ASSIMP/cimport.h"
#include "ASSIMP/scene.h"
#include "ASSIMP/postprocess.h"
#include "ASSIMP/material.h"

namespace SceneConversion
{
	void ConvertFilesForScene(string importFileName, string exportFolderName)
	{
		cout << "Converting files for <<" << importFileName.c_str() << ">>, exporting to <<" << exportFolderName.c_str() << ">>" << endl;
		// this process preset also INCLUDES the flag to make all faces based on triangles
		const aiScene* loadedScene = aiImportFile(importFileName.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);

		if (!loadedScene)
		{
			cout << "Could not load file <<" << importFileName << ">>" << endl;
			cout << "ASSIMP ERROR: "<< aiGetErrorString() << endl;
			return;
		}

		string folderPath = SceneStoragePath + exportFolderName;
		Core::IO::CreateFolderResult folderCreated = Core::IO::CreateFolder(folderPath);

		if (folderCreated == Core::IO::CreateFolderResult::Error)
		{
			cout << "Could not create folder at " << folderPath << ">>: ERROR" << endl;
			return;
		}
		else if (folderCreated == Core::IO::CreateFolderResult::AlreadyExists)
		{
			cout << "Could not create folder at " << folderPath << ">>: ALREADY EXISTS" << endl;
			CurrentExportFolder = folderPath;
		}
		else
		{
			cout << "Created folder at " << folderPath << ">>" << endl;
			CurrentExportFolder = folderPath;
		}

		uint32_t numberOfMeshes = loadedScene->mNumMeshes;

		for (uint32_t meshIndex = 0u; meshIndex < numberOfMeshes; meshIndex++)
		{
			cout << "Creating file for mesh <<" << meshIndex << ">> out of <<" << meshIndex << ">>" << endl;
			CreateFileForMesh(loadedScene, loadedScene->mMeshes[meshIndex], meshIndex, false); // update this bool to be correct once we allow importing of this type of mesh
		}

		cout << "Releasing memory for loading scene <<" << importFileName << ">>" << endl;
		// needs to be done since assimp holds all of the memeory management for loading
		aiReleaseImport(loadedScene);
	}

	void CreateFileForMesh(const aiScene* loadedScene, const aiMesh* mesh, uint32_t meshIndex, bool usesTexture)
	{
		cout << "Creating file to hold mesh information for <<" << mesh->mName.data << ">>" << endl;

		vector<aiVector3D> positions;
		positions.reserve(mesh->mNumVertices);

		vector<aiVector3D> normals;
		normals.reserve(mesh->mNumVertices);

		cout << "Reading positions and normals from ASSIMP mesh data..." << endl;
		// get vertices from assimp into our format
		for (uint32_t vertexIndex = 0u; vertexIndex < mesh->mNumVertices; vertexIndex++)
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

		string meshFileName = "MESH_" + to_string(meshIndex) + ".msh";
		Core::IO::File meshFile = Core::IO::File(Core::IO::FilePath{ CurrentExportFolder, meshFileName }, ios::out);
		meshFile.Open();

		if (!meshFile.FileStream.is_open())
		{
			cout << "Could not open file <<" << meshFile.GetFullPath() << ">>" << endl;
			return;
		}

		cout << "Writing to <<" << CurrentExportFolder << meshFileName << ">>" << endl;

		meshFile.Write("positions", mesh->mNumVertices);
		meshFile.CreateNewLine();
		for (uint32_t positionIndex = 0u; positionIndex < positions.size(); positionIndex++)
		{
			meshFile.Write((positions[positionIndex].x / 100.0f), (positions[positionIndex].y / 100.0f), (positions[positionIndex].z / 100.0f));
			meshFile.CreateNewLine();
		}

		meshFile.Write("normals", mesh->mNumVertices);
		meshFile.CreateNewLine();
		for (uint32_t normalIndex = 0u; normalIndex < normals.size(); normalIndex++)
		{
			meshFile.Write(normals[normalIndex].x, normals[normalIndex].y, normals[normalIndex].z);
			meshFile.CreateNewLine();
		}

		meshFile.Write("indices", mesh->mNumFaces * 3u);
		meshFile.CreateNewLine();
		for (uint32_t faceIndex = 0u; faceIndex < faces.size(); faceIndex += 3) // += 3 because 3 vertices to a face (triangles)
		{
			meshFile.Write(faces[faceIndex], faces[faceIndex + 1], faces[faceIndex + 2]);

			if (faceIndex < faces.size() - 1)
			{
				meshFile.CreateNewLine();
			}
		}

		meshFile.Close();

		// create file for material
		CreateFileForMaterial(loadedScene->mMaterials[mesh->mMaterialIndex], mesh->mMaterialIndex);
	}

	void CreateFileForMaterial(const aiMaterial* material, uint32_t materialIndex)
	{
		cout << "Creating file to hold material information for index <<" << materialIndex << ">> in file <<MATERIAL_" << materialIndex << ">>" << endl;
		// material values
		aiColor4D specularColor;
		aiColor4D diffuseColor;
		aiColor4D ambientColor;
		float shininess;

		cout << "Getting material information from assimp..." << endl;
		// get values from assimp material
		aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &specularColor);
		aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuseColor);
		aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &ambientColor);
		aiGetMaterialFloat(material, AI_MATKEY_SHININESS, &shininess);

		// store values in file
		string materialFileName = "MATERIAL_" + to_string(materialIndex) + ".mat";
		Core::IO::File materialFile = Core::IO::File(Core::IO::FilePath{ CurrentExportFolder, materialFileName }, ios::out);
		materialFile.Open();

		if (!materialFile.FileStream.is_open())
		{
			cout << "Could not open file <<" << CurrentExportFolder << materialFileName << ">>" << endl;
			return;
		}

		materialFile.Write("spec ", specularColor.r, specularColor.g, specularColor.b, specularColor.a);
		materialFile.CreateNewLine();
		materialFile.Write("diff", diffuseColor.r, diffuseColor.g, diffuseColor.b, diffuseColor.a);
		materialFile.CreateNewLine();
		materialFile.Write("amb", ambientColor.r, ambientColor.g, ambientColor.b, ambientColor.a);
		materialFile.CreateNewLine();
		materialFile.Write("shin", shininess);

		materialFile.Close();
	}
}
