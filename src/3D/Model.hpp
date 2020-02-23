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
#ifndef SRC_3D_MODEL_HPP_
#define SRC_3D_MODEL_HPP_

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>

#include "Mesh.hpp"
#include "Texture.hpp"
#include "Transformations.hpp"
#include "Vertex.hpp"

#include <assimp/scene.h>
#include <cmrc/cmrc.hpp>
#include <GL/glew.h>
#include <glm/gtx/euler_angles.hpp>


#include <vector>


namespace game_engine {
namespace _3D {

class Model : public Transformations {
	public:
		Model() = default;
		Model& operator=(const Model& rhs) = default;
		Model(const Model& rhs) = default;
		Model& operator=(Model&& rhs) noexcept = default;
		Model(Model&& rhs) noexcept = default;
		~Model() noexcept = default;

		explicit Model(Mesh mesh) {
			meshes_.push_back(mesh);
		}

		template<typename Renderer>
		Model(Renderer& renderer, const cmrc::embedded_filesystem& fs, const std::string& path, const bool gamma = false);

		template<typename Renderer>
		void LoadModel(Renderer& renderer, const cmrc::embedded_filesystem& fs, const std::string& path);

		template<typename Renderer>
		void Draw(const Renderer& renderer, const ShaderPrograms shaders = ShaderPrograms::DEFAULT);

	protected:
		/*  Functions   */
		template<typename Renderer>
		void ProcessNode(Renderer& renderer, aiNode* node, const aiScene* scene);

		template<typename Renderer>
		Mesh ProcessMesh(Renderer& renderer, aiMesh* mesh, const aiScene* scene);

		template<typename Renderer>
		std::vector<Texture> LoadMaterialTextures(const Renderer& renderer,
												  aiMaterial* mat,
												  aiTextureType type,
												  TextureType texture_type);

	public:
		static std::vector<Texture> textures_loaded_;

	protected:
		std::vector<Mesh> meshes_ { };
		const cmrc::embedded_filesystem* fs_ = nullptr;
		std::string directory_ { };
		std::string folder_ { };
		bool gamma_correction_ { };

		friend class Cube;
		friend std::ostream& operator<<(std::ostream& os, Model m);
};

} /* namespace _3D */
} /* namespace game_engine */

#include "Model.tpp"

#endif /* SRC_3D_MODEL_HPP_ */
