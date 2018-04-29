#include "DataExport\Rendering\Headers\SceneConversion.h"

#include "Core/Headers/ListDefs.h"
#include "Core/Headers/Hash.h"
#include "Core/Debugging/Headers/Macros.h"
#include "Core/IO/Headers/Folder.h"
#include "Core/IO/Headers/IOUtils.h"

#include "ASSIMP/cimport.h"
#include "ASSIMP/scene.h"
#include "ASSIMP/postprocess.h"
#include "ASSIMP/material.h"

using namespace Core;
using namespace Core::IO;

namespace Data
{
	namespace DataExport
	{
		void ConvertModelsInFolder(Ptr<File> directAssets, Ptr<File> sceneFile, String sceneName)
		{
			// in the future, this should likely also reference a database that is used to get specific file locations
			ConvertFilesForScene(directAssets, sceneFile, sceneName);
		}

		void ConvertFilesForScene(Ptr<File> directAssets, Ptr<File> sceneFile, String sceneName)
		{
			LOG("Converting files for <<" + sceneFile->GetFullPath() + ">>");
			// this process preset also INCLUDES the flag to make all faces based on triangles
			String fullPathCopy = sceneFile->GetFullPath();
			Ptr<const char> c_Path = fullPathCopy.c_str();
			const aiScene* loadedScene = aiImportFile(c_Path, aiProcessPreset_TargetRealtime_MaxQuality);

			if (!loadedScene)
			{
				LOG("Could not load file <<" + sceneFile->GetFullPath() + ">>");
				LOG("ASSIMP ERROR: " + String(aiGetErrorString()));
				return;
			}

			uint32_t numberOfMeshes = loadedScene->mNumMeshes;

			for (uint32_t meshIndex = 0u; meshIndex < numberOfMeshes; meshIndex++)
			{
				cout << "Creating file for mesh <<" << meshIndex << ">> out of <<" << meshIndex << ">>" << endl;
				CreateFileForMesh(directAssets, sceneName, loadedScene, loadedScene->mMeshes[meshIndex], meshIndex, false); // update this bool to be correct once we allow importing of this type of mesh
			}

			LOG("Releasing memory for loading scene <<" + sceneFile->GetFullPath() + ">>");
			// needs to be done since assimp holds all of the memeory management for loading
			aiReleaseImport(loadedScene);
		}

		void CreateFileForMesh(Core::Ptr<Core::IO::File> directAssets, String sceneName, const aiScene* loadedScene, const aiMesh* mesh, uint32_t meshIndex, bool usesTexture)
		{
			LOG("Creating file to hold mesh information for <<" + sceneName + ">>");

			vector<aiVector3D> positions;
			positions.reserve(mesh->mNumVertices);

			vector<aiVector3D> normals;
			normals.reserve(mesh->mNumVertices);

			LOG("Reading positions and normals from ASSIMP mesh data...");
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

			LOG("Reading [position/normal] indices used by each face...");
			for (uint32_t faceIndex = 0u; faceIndex < mesh->mNumFaces; faceIndex++)
			{
				// 3 indices for each face of the triangle
				faces.push_back(mesh->mFaces[faceIndex].mIndices[0u]);
				faces.push_back(mesh->mFaces[faceIndex].mIndices[1u]);
				faces.push_back(mesh->mFaces[faceIndex].mIndices[2u]);
			}

			FilePath meshFilePath = FilePath{ GetCWD() + "/Resources/ExportedAssets/Meshes/", ToString(HashValue(sceneName)) + ".msh" };
			File meshFile = File(meshFilePath, ios::out);
			meshFile.Open();

			if (!meshFile.FileStream.is_open())
			{
				LOG("Could not open file <<" + meshFilePath.GetFullPath() + ">>");
				return;
			}

			LOG("Writing to <<" + meshFilePath.GetFullPath() + ">>");

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
			CreateFileForMaterial(directAssets, sceneName, loadedScene->mMaterials[mesh->mMaterialIndex], mesh->mMaterialIndex);
		}

		void CreateFileForMaterial(Core::Ptr<Core::IO::File> directAssets, String sceneName, const aiMaterial* material, uint32_t materialIndex)
		{
			LOG("Creating file to hold material information for <<" + sceneName + ">>");

			// material values
			aiColor4D specularColor;
			aiColor4D diffuseColor;
			aiColor4D ambientColor;
			float shininess;

			LOG("Getting material information from assimp...");
			// get values from assimp material
			aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &specularColor);
			aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuseColor);
			aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &ambientColor);
			aiGetMaterialFloat(material, AI_MATKEY_SHININESS, &shininess);

			// store values in file
			FilePath materialFilePath = FilePath{ GetCWD() + "/Resources/ExportedAssets/Materials/", ToString(HashValue(sceneName)) + ".mat" };
			File materialFile = File(materialFilePath, ios::out);
			materialFile.Open();

			if (!materialFile.FileStream.is_open())
			{
				LOG("Could not open file <<" + materialFilePath.GetFullPath() + ">>");
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
}
