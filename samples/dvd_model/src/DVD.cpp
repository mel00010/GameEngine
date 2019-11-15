/******************************************************************************
 * DVD.cpp
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

#include "DVD.hpp"

#include <Log.hpp>
#include <3D/Texture.hpp>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtx/color_space.hpp>

using namespace GameEngine;

namespace DVD {

void DVD::setScale(glm::dvec2 _scale) {
	scale = _scale;
}

void DVD::setSpeed(float _speed) {
	speed = _speed;
}
void DVD::modifySpeed(float delta) {
	speed *= (1.0 + delta);
}
double DVD::getSpeed() {
	return speed;
}
void DVD::reset() {
	dvd.moveTo(glm::vec3(0.0));
}

void DVD::calculateMovement(float fps) {
	glm::vec3 scale_factor = glm::vec3(speed / (scale * fps * 4.0f), 0.0);
	glm::vec2 offset = (scale - glm::vec2(0.235, 0.115)) / scale;
	float length = glm::length(delta_vec * scale_factor);

	dvd.move(delta_vec * scale_factor);

	if(isAtWindowEdge(RIGHT, length, offset)) {
		delta_vec = glm::reflect(delta_vec, glm::vec3(1.0, 0.0, 0.0) + glm::vec3(glm::diskRand(0.05), 0.0));
		dvd.moveXTo(offset.x - length);
		updateLogoColor();
	}
	if(isAtWindowEdge(LEFT, length, offset)) {
		delta_vec = glm::reflect(delta_vec, glm::vec3(1.0, 0.0, 0.0) + glm::vec3(glm::diskRand(0.05), 0.0));
		dvd.moveXTo(-offset.x + length);
		updateLogoColor();
	}
	if(isAtWindowEdge(TOP, length, offset)) {
		delta_vec = glm::reflect(delta_vec, glm::vec3(0.0, 1.0, 0.0) + glm::vec3(glm::diskRand(0.05), 0.0));
		dvd.moveYTo(offset.y - length);
		updateLogoColor();
	}
	if(isAtWindowEdge(BOTTOM, length, offset)) {
		delta_vec = glm::reflect(delta_vec, glm::vec3(0.0, 1.0, 0.0) + glm::vec3(glm::diskRand(0.05), 0.0));
		dvd.moveYTo(-offset.y + length);
		updateLogoColor();
	}
	delta_vec = glm::normalize(delta_vec);
}

bool DVD::isAtWindowEdge(WindowEdge edge, float length, glm::vec2 offset) {
	switch(edge) {
		case RIGHT:		return length > (offset.x - dvd.position.x);
		case LEFT:		return length > (offset.x + dvd.position.x);
		case TOP:		return length > (offset.y - dvd.position.y);
		case BOTTOM:	return length > (offset.y + dvd.position.y);
	}
	return false;
}

void DVD::updateLogoColor() {
	glm::vec3 logo_color_hsv = glm::vec3(glm::linearRand(0.0, 360.0), 1.0, 1.0);
	logo_color = glm::rgbColor(logo_color_hsv);
}

} /* namespace DVD */
