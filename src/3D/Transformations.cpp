/******************************************************************************
 * Transformations.cpp
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

#include "Transformations.hpp"

#include <glm/gtx/euler_angles.hpp>

namespace game_engine {
namespace _3D {

void Transformations::Rotate(const glm::vec3 delta) {
	model_ *= glm::orientate4(delta);
	rotation_ += delta;
}
void Transformations::Rotate(const float delta_a, const float delta_b, const float delta_c) {
	Rotate(glm::vec3(delta_a, delta_b, delta_c));
}
void Transformations::RotateA(const float a) {
	Rotate(a, 0.0, 0.0);
}
void Transformations::RotateB(const float b) {
	Rotate(0.0, b, 0.0);
}
void Transformations::RotateC(const float c) {
	Rotate(0.0, 0.0, c);
}
void Transformations::RotateAB(const glm::vec2 delta) {
	Rotate(delta.x, delta.y, 0.0);
}
void Transformations::RotateAB(const float delta_a, const float delta_b) {
	Rotate(delta_a, delta_b, 0.0);
}
void Transformations::RotateAC(const glm::vec2 delta) {
	Rotate(delta.x, 0.0, delta.y);
}
void Transformations::RotateAC(const float delta_a, const float delta_c) {
	Rotate(delta_a, 0.0, delta_c);
}
void Transformations::RotateBC(const glm::vec2 delta) {
	Rotate(0.0, delta.x, delta.y);
}
void Transformations::RotateBC(const float delta_b, const float delta_c) {
	Rotate(0.0, delta_b, delta_c);
}

void Transformations::RotateTo(const glm::vec3 rot) {
	rotation_ = rot;
	model_ = glm::mat4(1.0f);
	model_ *= glm::orientate4(rotation_);
	model_ = glm::translate(model_, position_);
	model_ = glm::scale(model_, scaling_);
}
void Transformations::RotateTo(const float rot_a, const float rot_b, const float rot_c) {
	RotateTo(glm::vec3(rot_a, rot_b, rot_c));
}
void Transformations::RotateATo(const float a) {
	RotateTo(a, 0.0, 0.0);
}
void Transformations::RotateBTo(const float b) {
	RotateTo(0.0, b, 0.0);
}
void Transformations::RotateCTo(const float c) {
	RotateTo(0.0, 0.0, c);
}
void Transformations::RotateABTo(const glm::vec2 rot) {
	RotateTo(rot.x, rot.y, 0.0);
}
void Transformations::RotateABTo(const float rot_a, const float rot_b) {
	RotateTo(rot_a, rot_b, 0.0);
}
void Transformations::RotateACTo(const glm::vec2 rot) {
	RotateTo(rot.x, 0.0, rot.y);
}
void Transformations::RotateACTo(const float rot_a, const float rot_c) {
	RotateTo(rot_a, 0.0, rot_c);
}
void Transformations::RotateBCTo(const glm::vec2 rot) {
	RotateTo(0.0, rot.x, rot.y);
}
void Transformations::RotateBCTo(const float rot_b, const float rot_c) {
	RotateTo(0.0, rot_b, rot_c);
}


void Transformations::Move(const glm::vec3 delta) {
	model_ = glm::translate(model_, delta);
	position_ += delta;
}
void Transformations::Move(const float delta_x, const float delta_y, const float delta_z) {
	Move(glm::vec3(delta_x, delta_y, delta_z));
}
void Transformations::MoveX(const float x) {
	Move(x, 0.0, 0.0);
}
void Transformations::MoveY(const float y) {
	Move(0.0, y, 0.0);
}
void Transformations::MoveZ(const float z) {
	Move(0.0, 0.0, z);
}
void Transformations::MoveXY(const glm::vec2 delta) {
	Move(delta.x, delta.y, 0.0);
}
void Transformations::MoveXY(const float delta_x, const float delta_y) {
	Move(delta_x, delta_y, 0.0);
}
void Transformations::MoveXZ(const glm::vec2 delta) {
	Move(delta.x, 0.0, delta.y);
}
void Transformations::MoveXZ(const float delta_x, const float delta_z) {
	Move(delta_x, 0.0, delta_z);
}
void Transformations::MoveYZ(const glm::vec2 delta) {
	Move(0.0, delta.x, delta.y);
}
void Transformations::MoveYZ(const float delta_y, const float delta_z) {
	Move(0.0, delta_y, delta_z);
}

void Transformations::MoveTo(const glm::vec3 pos) {
	position_ = pos;
	model_ = glm::mat4(1.0f);
	model_ *= glm::orientate4(rotation_);
	model_ = glm::translate(model_, position_);
	model_ = glm::scale(model_, scaling_);
}
void Transformations::MoveTo(const float pos_x, const float pos_y, const float pos_z) {
	MoveTo(glm::vec3(pos_x, pos_y, pos_z));
}
void Transformations::MoveXTo(const float x) {
	MoveTo(x, 0.0, 0.0);
}
void Transformations::MoveYTo(const float y) {
	MoveTo(0.0, y, 0.0);
}
void Transformations::MoveZTo(const float z) {
	MoveTo(0.0, 0.0, z);
}
void Transformations::MoveXYTo(const glm::vec2 pos) {
	MoveTo(pos.x, pos.y, 0.0);
}
void Transformations::MoveXYTo(const float pos_x, const float pos_y) {
	MoveTo(pos_x, pos_y, 0.0);
}
void Transformations::MoveXZTo(const glm::vec2 pos) {
	MoveTo(pos.x, 0.0, pos.y);
}
void Transformations::MoveXZTo(const float pos_x, const float pos_z) {
	MoveTo(pos_x, 0.0, pos_z);
}
void Transformations::MoveYZTo(const glm::vec2 pos) {
	MoveTo(0.0, pos.x, pos.y);
}
void Transformations::MoveYZTo(const float pos_y, const float pos_z) {
	MoveTo(0.0, pos_y, pos_z);
}

void Transformations::Scale(const float Scale) {
	ScaleXYZ(Scale, Scale, Scale);
}
void Transformations::ScaleX(const float Scale) {
	ScaleXYZ(Scale, 1.0, 1.0);
}
void Transformations::ScaleY(const float Scale) {
	ScaleXYZ(Scale, Scale, 1.0);
}
void Transformations::ScaleZ(const float Scale) {
	ScaleXYZ(1.0, 1.0, Scale);
}
void Transformations::ScaleXY(const glm::vec2 Scale) {
	ScaleXYZ(Scale.x, Scale.y, 1.0);
}
void Transformations::ScaleXY(const float Scale_x, const float Scale_y) {
	ScaleXYZ(Scale_x, Scale_y, 1.0);
}
void Transformations::ScaleXZ(const glm::vec2 Scale) {
	ScaleXYZ(Scale.x, 1.0, Scale.y);
}
void Transformations::ScaleXZ(const float Scale_x, const float Scale_z) {
	ScaleXYZ(Scale_x, 1.0, Scale_z);
}
void Transformations::ScaleYZ(const glm::vec2 Scale) {
	ScaleXYZ(1.0, Scale.x, Scale.y);
}
void Transformations::ScaleYZ(const float Scale_y, const float Scale_z) {
	ScaleXYZ(1.0, Scale_y, Scale_z);
}
void Transformations::ScaleXYZ(const glm::vec3 Scale) {
	ScaleXYZ(Scale.x, Scale.y, Scale.z);
}
void Transformations::ScaleXYZ(const float Scale_x, const float Scale_y, const float Scale_z) {
	model_ = glm::scale(model_, glm::vec3(Scale_x, Scale_y, Scale_z));
	scaling_ *= glm::vec3(Scale_x, Scale_y, Scale_z);
}


void Transformations::ScaleTo(const float Scale) {
	ScaleXYZTo(Scale, Scale, Scale);
}
void Transformations::ScaleXTo(const float Scale) {
	ScaleXYZTo(Scale, 1.0, 1.0);
}
void Transformations::ScaleYTo(const float Scale) {
	ScaleXYZTo(Scale, Scale, 1.0);
}
void Transformations::ScaleZTo(const float Scale) {
	ScaleXYZTo(1.0, 1.0, Scale);
}
void Transformations::ScaleXYTo(const glm::vec2 Scale) {
	ScaleXYZTo(Scale.x, Scale.y, 1.0);
}
void Transformations::ScaleXYTo(const float Scale_x, const float Scale_y) {
	ScaleXYZTo(Scale_x, Scale_y, 1.0);
}
void Transformations::ScaleXZTo(const glm::vec2 Scale) {
	ScaleXYZTo(Scale.x, 1.0, Scale.y);
}
void Transformations::ScaleXZTo(const float Scale_x, const float Scale_z) {
	ScaleXYZTo(Scale_x, 1.0, Scale_z);
}
void Transformations::ScaleYZTo(const glm::vec2 Scale) {
	ScaleXYZTo(1.0, Scale.x, Scale.y);
}
void Transformations::ScaleYZTo(const float Scale_y, const float Scale_z) {
	ScaleXYZTo(1.0, Scale_y, Scale_z);
}
void Transformations::ScaleXYZTo(const glm::vec3 Scale) {
	ScaleXYZTo(Scale.x, Scale.y, Scale.z);
}
void Transformations::ScaleXYZTo(const float Scale_x, const float Scale_y, const float Scale_z) {
	scaling_ = glm::vec3(Scale_x, Scale_y, Scale_z);
	model_ = glm::mat4(1.0f);
	model_ *= glm::orientate4(rotation_);
	model_ = glm::translate(model_, position_);
	model_ = glm::scale(model_, scaling_);
}

} /* namespace _3D */
} /* namespace game_engine */


