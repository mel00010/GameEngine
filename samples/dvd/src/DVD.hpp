/******************************************************************************
 * DVD.hpp
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
#ifndef SAMPLES_DVD_SRC_DVD_HPP_
#define SAMPLES_DVD_SRC_DVD_HPP_

#include <GL/GL.hpp>
#include <Log.hpp>

#include <GL/glew.h>
#include <glm/glm.hpp>

using namespace GameEngine;

namespace DVD {

struct Vertex {
		glm::vec2 pos;
		glm::vec2 tex;
		Vertex(glm::vec2 _pos, glm::vec2 _tex) : pos(_pos), tex(_tex) {}
};

class DVD {
	public:
		DVD(GL::ProgramRef p);
		void draw(double& fps);

		void setScale(glm::dvec2 _scale) {
			scale = _scale;
		}

		void setSpeed(double _speed = 1.0) {
			speed = _speed;
		}
		void modifySpeed(double delta = 0.0) {
			speed *= (1.0 + delta);
		}
		double getSpeed() {
			return speed;
		}
		void reset() {
			translate_vec = glm::vec3(0.0);
		}

	protected:
		enum WindowEdge {
			TOP,
			BOTTOM,
			LEFT,
			RIGHT
		};
		bool isAtWindowEdge(WindowEdge edge, double length, glm::dvec2 offset);
		void updateLogoColor();

	protected:
		GL::ProgramRef p;
		GL::GL gl;

		glm::vec3 logo_color = glm::vec3(1.0, 1.0, 1.0);

		GLuint dvd_texture;

		glm::vec3 translate_vec = glm::vec3(0.0);
		glm::vec3 delta_vec = glm::normalize(glm::vec3(1.0, 1.0, 0.0));

		glm::dvec2 scale = glm::dvec2(1.0,1.0);
		double speed = 1.0;
};

} /* namespace DVD */


#endif /* SAMPLES_DVD_SRC_DVD_HPP_ */
