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

bool DVD::isAtWindowEdge(WindowEdge edge, double length, glm::dvec2 offset) {
	switch(edge) {
		case RIGHT:		return length > (offset.x - translate_vec.x);
		case LEFT:		return length > (offset.x + translate_vec.x);
		case TOP:		return length > (offset.y - translate_vec.y);
		case BOTTOM:	return length > (offset.y + translate_vec.y);
	}
	return false;
}

void DVD::updateLogoColor() {
	glm::vec3 logo_color_hsv = glm::vec3(glm::linearRand(0.0, 360.0), 1.0, 1.0);
	logo_color = glm::rgbColor(logo_color_hsv);
}

} /* namespace DVD */
