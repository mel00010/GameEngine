/******************************************************************************
 * Transformations.hpp
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
#ifndef SRC_3D_TRANSFORMATIONS_HPP_
#define SRC_3D_TRANSFORMATIONS_HPP_

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>

namespace game_engine {
namespace _3D {

class Transformations {
	public:
		void Rotate(const glm::vec3 delta);
		void Rotate(const float delta_a, const float delta_b, const float delta_c);
		void RotateA(const float a);
		void RotateB(const float b);
		void RotateC(const float c);
		void RotateAB(const glm::vec2 delta);
		void RotateAB(const float delta_a, const float delta_b);
		void RotateAC(const glm::vec2 delta);
		void RotateAC(const float delta_a, const float delta_c);
		void RotateBC(const glm::vec2 delta);
		void RotateBC(const float delta_b, const float delta_c);

		void RotateTo(const glm::vec3 rot);
		void RotateTo(const float rot_a, const float rot_b, const float rot_c);
		void RotateATo(const float a);
		void RotateBTo(const float b);
		void RotateCTo(const float c);
		void RotateABTo(const glm::vec2 rot);
		void RotateABTo(const float rot_a, const float rot_b);
		void RotateACTo(const glm::vec2 rot);
		void RotateACTo(const float rot_a, const float rot_c);
		void RotateBCTo(const glm::vec2 rot);
		void RotateBCTo(const float rot_b, const float rot_c);

		void Move(const glm::vec3 delta);
		void Move(const float delta_x, const float delta_y, const float delta_z);
		void MoveX(const float x);
		void MoveY(const float y);
		void MoveZ(const float z);
		void MoveXY(const glm::vec2 delta);
		void MoveXY(const float delta_x, const float delta_y);
		void MoveXZ(const glm::vec2 delta);
		void MoveXZ(const float delta_x, const float delta_z);
		void MoveYZ(const glm::vec2 delta);
		void MoveYZ(const float delta_y, const float delta_z);

		void MoveTo(const glm::vec3 pos);
		void MoveTo(const float pos_x, const float pos_y, const float pos_z);
		void MoveXTo(const float x);
		void MoveYTo(const float y);
		void MoveZTo(const float z);
		void MoveXYTo(const glm::vec2 pos);
		void MoveXYTo(float pos_x, const float pos_y);
		void MoveXZTo(const glm::vec2 pos);
		void MoveXZTo(float pos_x, const float pos_z);
		void MoveYZTo(const glm::vec2 pos);
		void MoveYZTo(const float pos_y, const float pos_z);

		void Scale(const float scale);
		void ScaleX(const float scale);
		void ScaleY(const float scale);
		void ScaleZ(const float scale);
		void ScaleXY(const glm::vec2 scale);
		void ScaleXY(const float scale_x, const float scale_y);
		void ScaleXZ(const glm::vec2 scale);
		void ScaleXZ(const float scale_x, const float scale_z);
		void ScaleYZ(const glm::vec2 scale);
		void ScaleYZ(const float scale_y, const float scale_z);
		void ScaleXYZ(const glm::vec3 scale);
		void ScaleXYZ(const float scale_x, const float scale_y, const float scale_z);

		void ScaleTo(const float scale);
		void ScaleXTo(const float scale);
		void ScaleYTo(const float scale);
		void ScaleZTo(const float scale);
		void ScaleXYTo(const glm::vec2 scale);
		void ScaleXYTo(const float scale_x, const float scale_y);
		void ScaleXZTo(const glm::vec2 scale);
		void ScaleXZTo(const float scale_x, const float scale_z);
		void ScaleYZTo(const glm::vec2 scale);
		void ScaleYZTo(const float scale_y, const float scale_z);
		void ScaleXYZTo(const glm::vec3 scale);
		void ScaleXYZTo(const float scale_x, const float scale_y, const float scale_z);

	public:
		glm::mat4 model_ = glm::mat4(1.0f);

		glm::vec3 rotation_;
		glm::vec3 scaling_;
		glm::vec3 position_;

		void swap(Transformations& other) noexcept {
			using std::swap;
			swap(other.model_, model_);
			swap(other.rotation_, rotation_);
			swap(other.scaling_, scaling_);
			swap(other.position_, position_);
		}
};

inline void swap(Transformations& a, Transformations& b) noexcept {
	a.swap(b);
}

} /* namespace _3D */
} /* namespace game_engine */

#endif /* SRC_3D_TRANSFORMATIONS_HPP_ */
