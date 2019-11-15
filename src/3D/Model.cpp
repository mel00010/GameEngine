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

Model::Model() :
		gammaCorrection(false) {
}
Model::Model(Mesh mesh) :
		gammaCorrection(false) {
	meshes.push_back(mesh);
}

void Model::rotate(glm::vec3 delta) {
	model *= glm::orientate4(delta);
	rotation += delta;
}
void Model::rotate(float delta_a, float delta_b, float delta_c) {
	rotate(glm::vec3(delta_a, delta_b, delta_c));
}
void Model::rotateA(float a) {
	rotate(a, 0.0, 0.0);
}
void Model::rotateB(float b) {
	rotate(0.0, b, 0.0);
}
void Model::rotateC(float c) {
	rotate(0.0, 0.0, c);
}
void Model::rotateAB(glm::vec2 delta) {
	rotate(delta.x, delta.y, 0.0);
}
void Model::rotateAB(float delta_a, float delta_b) {
	rotate(delta_a, delta_b, 0.0);
}
void Model::rotateAC(glm::vec2 delta) {
	rotate(delta.x, 0.0, delta.y);
}
void Model::rotateAC(float delta_a, float delta_c) {
	rotate(delta_a, 0.0, delta_c);
}
void Model::rotateBC(glm::vec2 delta) {
	rotate(0.0, delta.x, delta.y);
}
void Model::rotateBC(float delta_b, float delta_c) {
	rotate(0.0, delta_b, delta_c);
}

void Model::rotateTo(glm::vec3 rot) {
	rotation = rot;
	model = glm::mat4(1.0f);
	model *= glm::orientate4(rotation);
	model = glm::translate(model, position);
	model = glm::scale(model, scaling);
}
void Model::rotateTo(float rot_a, float rot_b, float rot_c) {
	rotateTo(glm::vec3(rot_a, rot_b, rot_c));
}
void Model::rotateATo(float a) {
	rotateTo(a, 0.0, 0.0);
}
void Model::rotateBTo(float b) {
	rotateTo(0.0, b, 0.0);
}
void Model::rotateCTo(float c) {
	rotateTo(0.0, 0.0, c);
}
void Model::rotateABTo(glm::vec2 rot) {
	rotateTo(rot.x, rot.y, 0.0);
}
void Model::rotateABTo(float rot_a, float rot_b) {
	rotateTo(rot_a, rot_b, 0.0);
}
void Model::rotateACTo(glm::vec2 rot) {
	rotateTo(rot.x, 0.0, rot.y);
}
void Model::rotateACTo(float rot_a, float rot_c) {
	rotateTo(rot_a, 0.0, rot_c);
}
void Model::rotateBCTo(glm::vec2 rot) {
	rotateTo(0.0, rot.x, rot.y);
}
void Model::rotateBCTo(float rot_b, float rot_c) {
	rotateTo(0.0, rot_b, rot_c);
}


void Model::move(glm::vec3 delta) {
	model = glm::translate(model, delta);
	position += delta;
}
void Model::move(float delta_x, float delta_y, float delta_z) {
	move(glm::vec3(delta_x, delta_y, delta_z));
}
void Model::moveX(float x) {
	move(x, 0.0, 0.0);
}
void Model::moveY(float y) {
	move(0.0, y, 0.0);
}
void Model::moveZ(float z) {
	move(0.0, 0.0, z);
}
void Model::moveXY(glm::vec2 delta) {
	move(delta.x, delta.y, 0.0);
}
void Model::moveXY(float delta_x, float delta_y) {
	move(delta_x, delta_y, 0.0);
}
void Model::moveXZ(glm::vec2 delta) {
	move(delta.x, 0.0, delta.y);
}
void Model::moveXZ(float delta_x, float delta_z) {
	move(delta_x, 0.0, delta_z);
}
void Model::moveYZ(glm::vec2 delta) {
	move(0.0, delta.x, delta.y);
}
void Model::moveYZ(float delta_y, float delta_z) {
	move(0.0, delta_y, delta_z);
}

void Model::moveTo(glm::vec3 pos) {
	position = pos;
	model = glm::mat4(1.0f);
	model *= glm::orientate4(rotation);
	model = glm::translate(model, position);
	model = glm::scale(model, scaling);
}
void Model::moveTo(float pos_x, float pos_y, float pos_z) {
	moveTo(glm::vec3(pos_x, pos_y, pos_z));
}
void Model::moveXTo(float x) {
	moveTo(x, 0.0, 0.0);
}
void Model::moveYTo(float y) {
	moveTo(0.0, y, 0.0);
}
void Model::moveZTo(float z) {
	moveTo(0.0, 0.0, z);
}
void Model::moveXYTo(glm::vec2 pos) {
	moveTo(pos.x, pos.y, 0.0);
}
void Model::moveXYTo(float pos_x, float pos_y) {
	moveTo(pos_x, pos_y, 0.0);
}
void Model::moveXZTo(glm::vec2 pos) {
	moveTo(pos.x, 0.0, pos.y);
}
void Model::moveXZTo(float pos_x, float pos_z) {
	moveTo(pos_x, 0.0, pos_z);
}
void Model::moveYZTo(glm::vec2 pos) {
	moveTo(0.0, pos.x, pos.y);
}
void Model::moveYZTo(float pos_y, float pos_z) {
	moveTo(0.0, pos_y, pos_z);
}

void Model::scale(float scale) {
	scaleXYZ(scale, scale, scale);
}
void Model::scaleX(float scale) {
	scaleXYZ(scale, 1.0, 1.0);
}
void Model::scaleY(float scale) {
	scaleXYZ(scale, scale, 1.0);
}
void Model::scaleZ(float scale) {
	scaleXYZ(1.0, 1.0, scale);
}
void Model::scaleXY(glm::vec2 scale) {
	scaleXYZ(scale.x, scale.y, 1.0);
}
void Model::scaleXY(float scale_x, float scale_y) {
	scaleXYZ(scale_x, scale_y, 1.0);
}
void Model::scaleXZ(glm::vec2 scale) {
	scaleXYZ(scale.x, 1.0, scale.y);
}
void Model::scaleXZ(float scale_x, float scale_z) {
	scaleXYZ(scale_x, 1.0, scale_z);
}
void Model::scaleYZ(glm::vec2 scale) {
	scaleXYZ(1.0, scale.x, scale.y);
}
void Model::scaleYZ(float scale_y, float scale_z) {
	scaleXYZ(1.0, scale_y, scale_z);
}
void Model::scaleXYZ(glm::vec3 scale) {
	scaleXYZ(scale.x, scale.y, scale.z);
}
void Model::scaleXYZ(float scale_x, float scale_y, float scale_z) {
	model = glm::scale(model, glm::vec3(scale_x, scale_y, scale_z));
	scaling *= glm::vec3(scale_x, scale_y, scale_z);
}


void Model::scaleTo(float scale) {
	scaleXYZTo(scale, scale, scale);
}
void Model::scaleXTo(float scale) {
	scaleXYZTo(scale, 1.0, 1.0);
}
void Model::scaleYTo(float scale) {
	scaleXYZTo(scale, scale, 1.0);
}
void Model::scaleZTo(float scale) {
	scaleXYZTo(1.0, 1.0, scale);
}
void Model::scaleXYTo(glm::vec2 scale) {
	scaleXYZTo(scale.x, scale.y, 1.0);
}
void Model::scaleXYTo(float scale_x, float scale_y) {
	scaleXYZTo(scale_x, scale_y, 1.0);
}
void Model::scaleXZTo(glm::vec2 scale) {
	scaleXYZTo(scale.x, 1.0, scale.y);
}
void Model::scaleXZTo(float scale_x, float scale_z) {
	scaleXYZTo(scale_x, 1.0, scale_z);
}
void Model::scaleYZTo(glm::vec2 scale) {
	scaleXYZTo(1.0, scale.x, scale.y);
}
void Model::scaleYZTo(float scale_y, float scale_z) {
	scaleXYZTo(1.0, scale_y, scale_z);
}
void Model::scaleXYZTo(glm::vec3 scale) {
	scaleXYZTo(scale.x, scale.y, scale.z);
}
void Model::scaleXYZTo(float scale_x, float scale_y, float scale_z) {
	scaling = glm::vec3(scale_x, scale_y, scale_z);
	model = glm::mat4(1.0f);
	model *= glm::orientate4(rotation);
	model = glm::translate(model, position);
	model = glm::scale(model, scaling);
}

std::ostream& operator<<(std::ostream& os, Model m) {
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
	os << "cmrc::embedded_filesystem* fs = " << m.fs << std::endl;
	os << "std::string directory = \"" << m.directory << "\"" << std::endl;
	os << "std::string folder = \"" << m.folder << "\"" << std::endl;
	os << "bool gammaCorrection = " << m.gammaCorrection << std::endl;

	os << pop_indent << "}";
	return os;
}

} /* namespace _3D */
} /* namespace GameEngine */
