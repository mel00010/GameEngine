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
#include <utility>

namespace game_engine {
namespace _3D {

class Camera {
	public:
		void Init(const glm::ivec2 size);
		void SetCameraRotation(glm::vec3 rotation);
		void SetCameraPos(const glm::vec3 pos);
		void RotateCamera(const double _yaw, const double _pitch);
		void MoveCamera(const glm::vec3 delta);
		void SetFov(const float _fov);
		void UpdateView();
		void UpdateProjection(glm::ivec2 size);

		template<typename Renderer>
		void DrawModel(const Renderer& renderer, Model& model, ShaderPrograms shaders = ShaderPrograms::DEFAULT);
		template<typename Renderer>
		void DrawModel(const Renderer& renderer, Cube& cube, ShaderPrograms shaders = ShaderPrograms::CUBE);
		template<typename Renderer>
		void DrawModel(const Renderer& renderer, Skybox& skybox, ShaderPrograms shaders = ShaderPrograms::SKYBOX);

		glm::ivec2 curr_size_;

		float fov_;
		double camera_speed_ = 0.01;
		double yaw_ = 0.0;
		double pitch_ = 15.0;

		glm::vec3 camera_pos_ = glm::vec3(0.0f, 0.5f, 3.0f);
		glm::vec3 camera_front_ = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 camera_up_ = glm::vec3(0.0f, 1.0f, 0.0f);

		glm::mat4 view_ = glm::mat4(1.0f);
		glm::mat4 projection_ = glm::mat4(1.0f);

		bool valid_ = false;

		void swap(Camera& other) noexcept {
			using std::swap;

			swap(other.curr_size_, curr_size_);
			swap(other.fov_, fov_);
			swap(other.camera_speed_, camera_speed_);
			swap(other.yaw_, yaw_);
			swap(other.pitch_, pitch_);
			swap(other.camera_pos_, camera_pos_);
			swap(other.camera_front_, camera_front_);
			swap(other.camera_up_, camera_up_);
			swap(other.view_, view_);
			swap(other.projection_, projection_);
		}
};

inline void swap(Camera& a, Camera& b) noexcept {
	a.swap(b);
}

} /* namespace _3D */
} /* namespace game_engine */

#include "Camera.tpp"

#endif /* SRC_3D_CAMERA_HPP_ */
