/******************************************************************************
 * Model.cpp
 * Copyright (C) 2019  Mel McCalla <melmccalla@gmail.com>
 *
 * This file is part of GameEngine.
 *
 * GameEngine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GameEngine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GameEngine.  If not, see <http://www.gnu.org/licenses/>.
 *****************************************************************************/

#include "Model.hpp"
#include "Vertex.hpp"

#include <Log.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace GameEngine {
namespace _3D {

std::vector<Texture> Model::textures_loaded;


void Model::rotate(glm::vec3 delta) {
	model *= glm::orientate4(delta);
}
void Model::move(glm::vec3 delta) {
	model = glm::translate(model, delta);
}
void Model::scale(double scale) {
	model = glm::scale(model, glm::vec3(scale, scale, scale));
}

void Model::draw(GL::ProgramRef prog) {
	for (auto& i : meshes) {
		i.draw(prog);
	}
}

void Model::loadModel(std::string path) {
	Assimp::Importer import;
	const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate
											   | aiProcess_FlipUVs
											   | aiProcess_JoinIdenticalVertices
											   | aiProcess_SortByPType);

	if (!scene || ( scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ) || !scene->mRootNode)
			{
		LOG_E("ASSIMP::" << import.GetErrorString());
		return;
	}
	directory = path.substr(0, path.find_last_of('/'));

	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene) {
	// process all the node's meshes (if any)
	for (size_t i = 0; i < node->mNumMeshes; i++) {
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	// then do the same for each of its children
	for (size_t i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
	// data to fill
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	// Walk through each of the mesh's vertices
	for (size_t i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;
		glm::vec2 vector2; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec2 first.
		glm::vec3 vector3; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
		glm::vec4 vector4; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec4 first.


		// positions
		if(mesh->HasPositions()) {
			vector3.x = mesh->mVertices[i].x;
			vector3.y = mesh->mVertices[i].y;
			vector3.z = mesh->mVertices[i].z;
			vertex.position = vector3;
		}

		// normals
		if(mesh->HasNormals()) { // does the mesh contain normals?
			vector3.x = mesh->mNormals[i].x;
			vector3.y = mesh->mNormals[i].y;
			vector3.z = mesh->mNormals[i].z;
			vertex.normal = vector3;
		}

		// texture coordinates
		if (mesh->HasTextureCoords(0)) { // does the mesh contain texture coordinate 0?
			vector2.x = mesh->mTextureCoords[0][i].x;
			vector2.y = mesh->mTextureCoords[0][i].y;
			vertex.tex_coord0 = vector2;
		}
		if (mesh->HasTextureCoords(1)) { // does the mesh contain texture coordinate 1?
			vector2.x = mesh->mTextureCoords[1][i].x;
			vector2.y = mesh->mTextureCoords[1][i].y;
			vertex.tex_coord1 = vector2;
		}
		if (mesh->HasTextureCoords(2)) { // does the mesh contain texture coordinate 2?
			vector2.x = mesh->mTextureCoords[2][i].x;
			vector2.y = mesh->mTextureCoords[2][i].y;
			vertex.tex_coord2 = vector2;
		}
		if (mesh->HasTextureCoords(3)) { // does the mesh contain texture coordinate 3?
			vector2.x = mesh->mTextureCoords[3][i].x;
			vector2.y = mesh->mTextureCoords[3][i].y;
			vertex.tex_coord3 = vector2;
		}
		if (mesh->HasTextureCoords(4)) { // does the mesh contain texture coordinate 4?
			vector2.x = mesh->mTextureCoords[4][i].x;
			vector2.y = mesh->mTextureCoords[4][i].y;
			vertex.tex_coord4 = vector2;
		}
		if (mesh->HasTextureCoords(5)) { // does the mesh contain texture coordinate 5?
			vector2.x = mesh->mTextureCoords[5][i].x;
			vector2.y = mesh->mTextureCoords[5][i].y;
			vertex.tex_coord5 = vector2;
		}
		if (mesh->HasTextureCoords(6)) { // does the mesh contain texture coordinate 6?
			vector2.x = mesh->mTextureCoords[6][i].x;
			vector2.y = mesh->mTextureCoords[6][i].y;
			vertex.tex_coord6 = vector2;
		}
		if (mesh->HasTextureCoords(7)) { // does the mesh contain texture coordinate 7?
			vector2.x = mesh->mTextureCoords[7][i].x;
			vector2.y = mesh->mTextureCoords[7][i].y;
			vertex.tex_coord7 = vector2;
		}

		// colors
		if (mesh->HasVertexColors(0)) { // does the mesh contain primary vertex colors?
			vector4.r = mesh->mColors[0][i].r;
			vector4.g = mesh->mColors[0][i].g;
			vector4.b = mesh->mColors[0][i].b;
			vector4.a = mesh->mColors[0][i].a;
			vertex.color = vector4;
		}
		if (mesh->HasVertexColors(1)) { // does the mesh contain secondary vertex colors?
			vector4.r = mesh->mColors[1][i].r;
			vector4.g = mesh->mColors[1][i].g;
			vector4.b = mesh->mColors[1][i].b;
			vector4.a = mesh->mColors[1][i].a;
			vertex.secondary_color = vector4;
		}

		if (mesh->HasTangentsAndBitangents()) {  // does the mesh contain tangents and bitangents?
			// tangent
			vector3.x = mesh->mTangents[i].x;
			vector3.y = mesh->mTangents[i].y;
			vector3.z = mesh->mTangents[i].z;
			vertex.tangent = vector3;

			// bitangent
			vector3.x = mesh->mBitangents[i].x;
			vector3.y = mesh->mBitangents[i].y;
			vector3.z = mesh->mBitangents[i].z;
			vertex.bitangent = vector3;
		}
		vertices.push_back(vertex);
	}
	// now walk through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	for (size_t i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		for (size_t j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}
	// process materials
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	// we assume a convention for sampler names in the shaders. Each diffuse texture should be named
	// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
	// Same applies to other texture as the following list summarizes:
	// diffuse: texture_diffuseN
	// specular: texture_specularN
	// normal: texture_normalN

	// 1. diffuse maps
	std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, TextureType::DIFFUSE);
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	// 2. specular maps
	std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, TextureType::SPECULAR);
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	// 3. normal maps
	std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, TextureType::NORMAL);
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	// 4. height maps
	std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, TextureType::HEIGHT);
	textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	Primitive mode = Primitive::TRIANGLES;
	switch(mesh->mPrimitiveTypes) {
		case aiPrimitiveType_POINT:
			mode = Primitive::POINTS;
			break;
		case aiPrimitiveType_LINE:
			glLineWidth(3.0);
			mode = Primitive::LINES;
			break;
		case aiPrimitiveType_TRIANGLE:
			mode = Primitive::TRIANGLES;
			break;
	}
	// return a mesh object created from the extracted mesh data
	return Mesh(vertices, indices, textures, mode);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, TextureType texture_type) {
	std::vector<Texture> textures;
	for (size_t i = 0; i < mat->GetTextureCount(type); i++) {
		aiString str;
		mat->GetTexture(type, i, &str);
		// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		bool skip = false;
		for (size_t j = 0; j < textures_loaded.size(); j++) {
			if (textures_loaded[j].path == (directory + "/" + std::string(str.C_Str()))) {
				textures.push_back(textures_loaded[j]);
				skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip) {	// if texture hasn't been loaded already, load it
//			LOG_D("Loading new texture " << mat->GetName().C_Str());
			Texture texture(directory + "/" + std::string(str.C_Str()), texture_type);
			textures.push_back(texture);
			textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
		}
	}
	return textures;
}
} /* namespace _3D */
} /* namespace GameEngine */
