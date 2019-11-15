/******************************************************************************
 * Camera.hpp
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
#ifndef SRC_3D_CAMERA_HPP_
#define SRC_3D_CAMERA_HPP_

#include "Cube.hpp"
#include "Model.hpp"
#include "Skybox.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <SDL2/SDL.h>

namespace GameEngine {
namespace _3D {

class Camera {
	public:
		void init(glm::ivec2 size);
		void setCameraRotation(glm::vec3 rotation);
		void setCameraPos(glm::vec3 pos);
		void rotateCamera(double _yaw, double _pitch);
		void moveCamera(glm::vec3 delta);
		void setFOV(float _fov);
		void updateView();
		void updateProjection(glm::ivec2 size);

		template<typename Renderer>
			void drawModel(Renderer& renderer, Model& model, ShaderPrograms shaders = ShaderPrograms::DEFAULT);
		template<typename Renderer>
			void drawModel(Renderer& renderer, Cube& model, ShaderPrograms shaders = ShaderPrograms::DEFAULT);
		template<typename Renderer>
			void drawModel(Renderer& renderer, Skybox& model, ShaderPrograms shaders = ShaderPrograms::DEFAULT);
		glm::ivec2 curr_size;

		float fov;
		double cameraSpeed = 0.01;
		double yaw = 0.0;
		double pitch = 15.0;

		glm::vec3 cameraPos = glm::vec3(0.0f, 0.5f, 3.0f);
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f,  0.0f);

		glm::mat4 view			= glm::mat4(1.0f);
		glm::mat4 projection	= glm::mat4(1.0f);

		bool valid = false;
};

} /* namespace _3D */
} /* namespace GameEngine */

#include "Camera.tpp"

#endif /* SRC_3D_CAMERA_HPP_ */
