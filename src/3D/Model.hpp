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
#include "Vertex.hpp"

#include <assimp/scene.h>
#include <cmrc/cmrc.hpp>
#include <GL/glew.h>
#include <glm/gtx/euler_angles.hpp>


#include <vector>


namespace GameEngine {
namespace _3D {

class Model {
	public:
		Model();
		Model(Mesh mesh);

		template<typename Renderer>
		Model(Renderer& renderer, cmrc::embedded_filesystem& fs, const std::string& path, bool gamma = false);

		template<typename Renderer>
		void loadModel(Renderer& renderer, cmrc::embedded_filesystem& fs, const std::string& path);

		template<typename Renderer>
		void draw(Renderer& renderer, ShaderPrograms shaders = ShaderPrograms::DEFAULT);

	public:
		void rotate(glm::vec3 delta);
		void rotate(float delta_a, float delta_b, float delta_c);
		void rotateA(float a);
		void rotateB(float b);
		void rotateC(float c);
		void rotateAB(glm::vec2 delta);
		void rotateAB(float delta_a, float delta_b);
		void rotateAC(glm::vec2 delta);
		void rotateAC(float delta_a, float delta_c);
		void rotateBC(glm::vec2 delta);
		void rotateBC(float delta_b, float delta_c);

		void rotateTo(glm::vec3 rot);
		void rotateTo(float rot_a, float rot_b, float rot_c);
		void rotateATo(float a);
		void rotateBTo(float b);
		void rotateCTo(float c);
		void rotateABTo(glm::vec2 rot);
		void rotateABTo(float rot_a, float rot_b);
		void rotateACTo(glm::vec2 rot);
		void rotateACTo(float rot_a, float rot_c);
		void rotateBCTo(glm::vec2 rot);
		void rotateBCTo(float rot_b, float rot_c);

		void move(glm::vec3 delta);
		void move(float delta_x, float delta_y, float delta_z);
		void moveX(float x);
		void moveY(float y);
		void moveZ(float z);
		void moveXY(glm::vec2 delta);
		void moveXY(float delta_x, float delta_y);
		void moveXZ(glm::vec2 delta);
		void moveXZ(float delta_x, float delta_z);
		void moveYZ(glm::vec2 delta);
		void moveYZ(float delta_y, float delta_z);

		void moveTo(glm::vec3 pos);
		void moveTo(float pos_x, float pos_y, float pos_z);
		void moveXTo(float x);
		void moveYTo(float y);
		void moveZTo(float z);
		void moveXYTo(glm::vec2 pos);
		void moveXYTo(float pos_x, float pos_y);
		void moveXZTo(glm::vec2 pos);
		void moveXZTo(float pos_x, float pos_z);
		void moveYZTo(glm::vec2 pos);
		void moveYZTo(float pos_y, float pos_z);

		void scale(float scale);
		void scaleX(float scale);
		void scaleY(float scale);
		void scaleZ(float scale);
		void scaleXY(glm::vec2 scale);
		void scaleXY(float scale_x, float scale_y);
		void scaleXZ(glm::vec2 scale);
		void scaleXZ(float scale_x, float scale_z);
		void scaleYZ(glm::vec2 scale);
		void scaleYZ(float scale_y, float scale_z);
		void scaleXYZ(glm::vec3 scale);
		void scaleXYZ(float scale_x, float scale_y, float scale_z);

		void scaleTo(float scale);
		void scaleXTo(float scale);
		void scaleYTo(float scale);
		void scaleZTo(float scale);
		void scaleXYTo(glm::vec2 scale);
		void scaleXYTo(float scale_x, float scale_y);
		void scaleXZTo(glm::vec2 scale);
		void scaleXZTo(float scale_x, float scale_z);
		void scaleYZTo(glm::vec2 scale);
		void scaleYZTo(float scale_y, float scale_z);
		void scaleXYZTo(glm::vec3 scale);
		void scaleXYZTo(float scale_x, float scale_y, float scale_z);

	protected:
		/*  Functions   */
		template<typename Renderer>
		void processNode(Renderer& renderer, aiNode* node, const aiScene* scene);

		template<typename Renderer>
		Mesh processMesh(Renderer& renderer, aiMesh* mesh, const aiScene* scene);

		template<typename Renderer>
		std::vector<Texture> loadMaterialTextures(Renderer& renderer, aiMaterial* mat, aiTextureType type, TextureType texture_type);

	public:
		glm::mat4 model = glm::mat4(1.0f);

		glm::vec3 rotation;
		glm::vec3 scaling;
		glm::vec3 position;

		static std::vector<Texture> textures_loaded;

	protected:
		friend class Cube;

		std::vector<Mesh> meshes;
		cmrc::embedded_filesystem* fs = nullptr;
		std::string directory;
		std::string folder;
		bool gammaCorrection;
		friend std::ostream& operator<<(std::ostream& os, Model m);
};

} /* namespace _3D */
} /* namespace GameEngine */

#include "Model.tpp"

#endif /* SRC_3D_MODEL_HPP_ */
