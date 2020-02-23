/******************************************************************************
 * Model.tpp
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
#ifndef SRC_3D_MODEL_TPP_
#define SRC_3D_MODEL_TPP_

#include "Model.hpp"

#include "EmbeddedIOHandler.hpp"
#include "Vertex.hpp"

#include <Log.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace game_engine {
namespace _3D {

inline glm::vec2 Convert(const aiVector2D vec) {
	return glm::vec2(vec.x, vec.y);
}
inline glm::vec3 Convert(const aiVector3D vec) {
	return glm::vec3(vec.x, vec.y, vec.z);
}
inline glm::vec3 Convert(const aiColor3D vec) {
	return glm::vec3(vec.r, vec.g, vec.b);
}
inline glm::vec4 Convert(const aiColor4D vec) {
	return glm::vec4(vec.r, vec.g, vec.b, vec.a);
}

template<typename Renderer>
Model::Model(Renderer& renderer, const cmrc::embedded_filesystem& fs,  const std::string& path, const bool gamma) :
		gamma_correction_(gamma) {
	LoadModel(renderer, fs, path);
}

template<typename Renderer>
void Model::LoadModel(Renderer& renderer, const cmrc::embedded_filesystem& _fs, const std::string& path) {
	directory_ = path;
//	LOG_D("directory = " << directory);
	if(path.rfind('/') == std::string::npos) {
		folder_ = path;
	} else {
		folder_ = path.substr(path.rfind('/'));
	}
//	LOG_D("folder = " << folder);

	fs_ = &_fs;

	EmbeddedIOHandler* io_handler = new EmbeddedIOHandler(*fs_);

	Assimp::Importer import;
	import.SetExtraVerbose(true);
	import.SetIOHandler(io_handler);

	const aiScene *scene = import.ReadFile((path + "/" + folder_ + ".obj").c_str(),
			  aiProcess_Triangulate
			| aiProcess_FlipUVs
			| aiProcess_JoinIdenticalVertices
			| aiProcess_SortByPType);
//	LOG_D("Imported file " << (path + "/" + folder + ".obj"));
	if ((!scene) || (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) || (!scene->mRootNode)) {
		LOG_E("ASSIMP::" << import.GetErrorString());
		return;
	}

	ProcessNode(renderer, scene->mRootNode, scene);
}

template<typename Renderer>
void Model::ProcessNode(Renderer& renderer, aiNode* node, const aiScene* scene) {
	// process all the node's meshes (if any)
	for (size_t i = 0; i < node->mNumMeshes; i++) {
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		meshes_.push_back(ProcessMesh(renderer, mesh, scene));
	}
	// then do the same for each of its children
	for (size_t i = 0; i < node->mNumChildren; i++) {
		ProcessNode(renderer, node->mChildren[i], scene);
	}
}

template<typename Renderer>
Mesh Model::ProcessMesh(Renderer& renderer, aiMesh* mesh, const aiScene* scene) {
	// data to fill
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	// Walk through each of the mesh's vertices
	for (GLuint i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;

		// positions
		if(mesh->HasPositions()) { // does the mesh contain positions?
			vertex.position = Convert(mesh->mVertices[i]);
		}

		// normals
		if(mesh->HasNormals()) { // does the mesh contain normals?
			vertex.normal = Convert(mesh->mNormals[i]);
		}

		// texture coordinates
		if (mesh->HasTextureCoords(0)) { // does the mesh contain texture coordinate 0?
			vertex.tex_coord0 = Convert(mesh->mTextureCoords[0][i]);
		}
		if (mesh->HasTextureCoords(1)) { // does the mesh contain texture coordinate 1?
			vertex.tex_coord1 = Convert(mesh->mTextureCoords[1][i]);
		}
		if (mesh->HasTextureCoords(2)) { // does the mesh contain texture coordinate 2?
			vertex.tex_coord2 = Convert(mesh->mTextureCoords[2][i]);
		}
		if (mesh->HasTextureCoords(3)) { // does the mesh contain texture coordinate 3?
			vertex.tex_coord3 = Convert(mesh->mTextureCoords[3][i]);
		}
		if (mesh->HasTextureCoords(4)) { // does the mesh contain texture coordinate 4?
			vertex.tex_coord4 = Convert(mesh->mTextureCoords[4][i]);
		}
		if (mesh->HasTextureCoords(5)) { // does the mesh contain texture coordinate 5?
			vertex.tex_coord5 = Convert(mesh->mTextureCoords[5][i]);
		}
		if (mesh->HasTextureCoords(6)) { // does the mesh contain texture coordinate 6?
			vertex.tex_coord6 = Convert(mesh->mTextureCoords[6][i]);
		}
		if (mesh->HasTextureCoords(7)) { // does the mesh contain texture coordinate 7?
			vertex.tex_coord7 = Convert(mesh->mTextureCoords[7][i]);
		}

		// colors
		if (mesh->HasVertexColors(0)) { // does the mesh contain primary vertex colors?
			vertex.color = Convert(mesh->mColors[0][i]);
		}
		if (mesh->HasVertexColors(1)) { // does the mesh contain secondary vertex colors?
			vertex.secondary_color = Convert(mesh->mColors[1][i]);
		}

		if (mesh->HasTangentsAndBitangents()) {  // does the mesh contain tangents and bitangents?
			vertex.tangent = Convert(mesh->mTangents[i]);
			vertex.bitangent = Convert(mesh->mBitangents[i]);
		}
		vertices.push_back(vertex);
	}

	// now walk through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	for (GLuint i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		for (GLuint j = 0; j < face.mNumIndices; j++) {
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
	std::vector<Texture> diffuseMaps = LoadMaterialTextures(renderer, material, aiTextureType_DIFFUSE, TextureType::DIFFUSE);
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	// 2. specular maps
	std::vector<Texture> specularMaps = LoadMaterialTextures(renderer, material, aiTextureType_SPECULAR, TextureType::SPECULAR);
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	// 3. normal maps
	std::vector<Texture> normalMaps = LoadMaterialTextures(renderer, material, aiTextureType_HEIGHT, TextureType::NORMAL);
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	// 4. height maps
	std::vector<Texture> heightMaps = LoadMaterialTextures(renderer, material, aiTextureType_AMBIENT, TextureType::HEIGHT);
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
	Mesh _mesh(vertices, indices, textures, mode);
	_mesh.Init(renderer, ShaderPrograms::DEFAULT);
//	mesh_.setupMesh(renderer);
	return _mesh;
}

template<typename Renderer>
std::vector<Texture> Model::LoadMaterialTextures(
		const Renderer& renderer,
		aiMaterial* mat, aiTextureType type, TextureType texture_type) {

	std::vector<Texture> textures;
//	LOG_D(mat->GetTextureCount(type));
	for (GLuint i = 0; i < mat->GetTextureCount(type); i++) {
		aiString str;
		mat->GetTexture(type, i, &str);
		// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		bool skip = false;
		for (GLuint j = 0; j < textures_loaded_.size(); j++) {
			if (textures_loaded_[j].path_ == (directory_ + "/" + std::string(str.C_Str()))) {
				textures.push_back(textures_loaded_[j]);
				skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip) {	// if texture hasn't been loaded already, load it
//			LOG_D("Loading new texture " << mat->GetName().C_Str());
			Texture texture;
			cmrc::file file = fs_->open(directory_ + "/" + std::string(str.C_Str()));
//			LOG_D("Opening texture " << file.path());
			texture.LoadTexture(renderer, file, ShaderPrograms::DEFAULT, texture_type);
			textures.push_back(texture);
			textures_loaded_.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecessary load duplicate textures.
		}
	}
	return textures;
}


template<typename Renderer> void Model::Draw(const Renderer& renderer, const ShaderPrograms shaders) {
	for (auto& i : meshes_) {
		i.Draw(renderer, shaders);
	}
}

} /* namespace _3D */
} /* namespace game_engine */

#endif /* SRC_3D_MODEL_TPP_ */
