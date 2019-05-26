/******************************************************************************
 * Model.hpp
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
#ifndef SRC_MODEL_HPP_
#define SRC_MODEL_HPP_

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>

#include <GL/GL.hpp>
#include <GL/Program.hpp>

#include <Util/ResourceDefs.hpp>

#include "Mesh.hpp"
#include "Primitive.hpp"
#include "Texture.hpp"
#include "Vertex.hpp"

#include <assimp/scene.h>
#include <GL/glew.h>
#include <glm/gtx/euler_angles.hpp>
#include <Log.hpp>

#include <vector>


namespace GameEngine {
namespace _3D {

class Model {
	public:
		Model() : gammaCorrection(false) {}
		Model(Mesh mesh) : gammaCorrection(false) {
			meshes.push_back(mesh);
		}
		Model(const std::string& path, bool gamma = false) : gammaCorrection(gamma) {
			loadModel(path);
		}
		template <Enum ResourceID> Model(const Resource<ResourceID> resource, bool gamma = false)
				: gammaCorrection(gamma) {
			loadModel(resource);
		}
		template <Enum ResourceID> void loadModel(const Resource<ResourceID> resource) {
			std::string file_location;
			char *base_path = SDL_GetBasePath();
			if (base_path) {
				file_location = base_path;
			} else {
				file_location = "./";
			}
			file_location += std::string(resource.file_path) + "/" + std::string(resource.main_file);
			loadModel(file_location);
		}
		void loadModel(std::string path);

		void draw(GL::ProgramRef prog);
	public:
		void rotate(glm::vec3 delta);
		void move(glm::vec3 delta);
		void scale(double scale);

	protected:
		/*  Functions   */
		void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, TextureType texture_type);

	public:
		glm::mat4 model = glm::mat4(1.0f);
		static std::vector<Texture> textures_loaded;

	protected:
		std::vector<Mesh> meshes;
		std::string directory;
		bool gammaCorrection;
		friend std::ostream& operator<<(std::ostream& os, Model m);
};

inline std::ostream& operator<<(std::ostream& os, Model m) {
	os << "Model {" << std::endl << push_indent;

	os << "glm::mat4 model = " << push_indent << m.model << pop_indent << std::endl;

	os << "std::vector<Texture> textures_loaded = { " << std::endl;
	os << push_indent;
	for (auto& i : m.textures_loaded) {
		os << i << ", " << std::endl;
	}
	os << pop_indent;
	os << "}" << std::endl;

	os << "std::vector<Mesh> meshes = {" << std::endl;
	os << push_indent;
	for (auto& i : m.meshes) {
		os << i << ", " << std::endl;
	}
	os << pop_indent;
	os << "}" << std::endl;

	os << "std::string directory = \"" << m.directory << "\"" << std::endl;
	os << "bool gammaCorrection = " << m.gammaCorrection << std::endl;

	os << pop_indent << "}";
	return os;
}

} /* namespace _3D */
} /* namespace GameEngine */
#endif /* SRC_MODEL_HPP_ */
