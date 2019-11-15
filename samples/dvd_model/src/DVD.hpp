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

#include <3D/Camera.hpp>
#include <3D/Model.hpp>
#include <3D/Texture.hpp>
#include <Renderer.hpp>
#include <Vertex.hpp>


#include <Util/UUID.hpp>
#include <Log.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <GL/glew.h>

#include <cmrc/cmrc.hpp>

CMRC_DECLARE(DVD);

using namespace GameEngine;

namespace DVD {

class DVD {
	public:
		template<typename Renderer> DVD(Renderer& renderer) {
			dvd = _3D::Model(renderer, fs, "dvd");

			glm::ivec2 size = renderer.getWindowSize();
			projection = glm::ortho(0.0f, static_cast<float>(size.x), 0.0f, static_cast<float>(size.y));

			updateLogoColor();
			delta_vec = glm::vec3(glm::circularRand(1.0), 0.0);

			dvd.scaleXY(0.5f/scale);
		}

		void calculateMovement(float fps);

		template<typename Renderer>
		void draw(Renderer& renderer, float fps) {
			calculateMovement(fps);
			renderer.setColor(ShaderPrograms::DEFAULT, logo_color);
			renderer.setMatrices(ShaderPrograms::DEFAULT, dvd.model, view, projection);
			dvd.draw(renderer);
		}

		void setScale(glm::dvec2 _scale);
		void setSpeed(float _speed = 1.0);
		void modifySpeed(float delta = 0.0);
		double getSpeed();
		void reset();

	protected:
		enum WindowEdge {
			TOP,
			BOTTOM,
			LEFT,
			RIGHT
		};
		bool isAtWindowEdge(WindowEdge edge, float length, glm::vec2 offset);
		void updateLogoColor();

	protected:
		cmrc::embedded_filesystem fs = cmrc::DVD::get_filesystem();

		glm::vec3 logo_color = glm::vec3(1.0, 1.0, 1.0);

		_3D::Texture dvd_texture;
		_3D::Model dvd;
		glm::mat4 view			= glm::mat4(1.0f);
		glm::mat4 projection	= glm::mat4(1.0f);
		VBO_handle handle;

		glm::vec3 delta_vec = glm::normalize(glm::vec3(1.0, 1.0, 0.0));

		glm::vec2 scale = glm::vec2(1.0,1.0);
		float speed = 1.0;
};

} /* namespace DVD */


#endif /* SAMPLES_DVD_SRC_DVD_HPP_ */
