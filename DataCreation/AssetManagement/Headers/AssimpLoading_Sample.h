/*
#pragma once

#include <vector>
#include <iostream>

#include "ASSIMP\Compiler\cimport.h"
#include "ASSIMP\Compiler\scene.h"
#include "ASSIMP\Compiler\postprocess.h"
#include "ASSIMP\Compiler\material.h"

using namespace std;

namespace TestingAssimpLoading
{
	struct Model
	{
		struct Mesh
		{

		};
		// Transform transform;
		vector<Mesh> meshes;
		vector<float> vertices;

		std::shared_ptr<Model> LoadModelFromFile(const char* fileName)
		{
			// this process preset also INCLUDES the flag to make all faces based on triangles
			const aiScene* scene = aiImportFile(fileName, aiProcessPreset_TargetRealtime_MaxQuality);

			if (!scene)
			{
				std::cout << "Could not load file " << fileName << ": " << aiGetErrorString() << std::endl;
			}

			vecotr<Mesh> meshes;
			meshes.reserve(scene->mNumMeshes); // std::vector increases by twice the size whenever it expands, reserving the size allows us to minimize the final size (and is just more efficient)

			for (uint32_t meshIndex = 0u; meshIndex < scene->mNumMEshes; meshIndex++)
			{
				aiMesh* mesh = scene->mMeshes[meshIndex];

				vector<MaterialOnlyShader::Vertex> vertices;
				vertices.reserve(mesh->mNumVertices);

				// get material for this mesh from assimp
				aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
				aiColor4D specularColor;
				aiColor4D diffuseColor;
				aiColor4D ambientColot;
				float shininess;

				aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &specularColor);
				aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuseColor);
				aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &ambientColot);
				aigGetMaterialFloat(material, AI_MATKEY_SHININESS, &shininess);

				// create our engine material from the information received from assimp
				MaterialOnlyShader::Material meshMaterial
				{
					Color(specularColor),
					Color(diffuseColor),
					Color(ambientcolor)
				};

				// get vertices from assimp into our format
				for (std::uint32 vertId = 0u; vertId < mesh->mNumVertices; vertId++)
				{
					// get vertex and normal from mesh data
					aiVector3D pos = mesh->mVertices[vertId];
					aiVector3D norm = mesh->mVNormals[vertId];

					// add information into list of vertices for our mesh
					vertices.push_back(
							MaterialOnlyShader::Vertex(pos, norm)
						)
				}

				// get all indices out of assimp format int othe vector
				vector<uint32_t> indices;
				indices.reserver(mesh->mNumFaces * 3u); // 3 indices per triangle

				for (uint32_t faceId = 0u; faceId < mesh->mNumFaces; faceId++)
				{
					// 3 indices for each face of the triangle
					indices.push_back(mesh->mFaces[faceId].mIndices[0u]);
					indices.push_back(mesh->mFaces[faceId].mIndices[1u]);
					indices.push_back(mesh->mFaces[faceId].mIndices[2u]);
				}

				// make render call
				MAterialOnlyShader::RenderCall call(device, vertices, indices); // we do not need this as we will be doing ours differently

				meshes.push_back({ call, meshMaterial });  // we do not need to pass in a call as we will be doing ours differently
			}

			// needs to be done since assimp holds all of the memeory management for loading
			aiReleaseImport(scene);

			return make_shared<Model>(meshes, transform);
		}
	};
}
*/