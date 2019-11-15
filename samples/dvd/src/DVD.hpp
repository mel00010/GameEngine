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
			dvd_texture = _3D::Texture(renderer, fs.open("dvd.png"), ShaderPrograms::DEFAULT, _3D::TextureType::DIFFUSE);

			updateLogoColor();

			vertices.push_back(Vertex(glm::vec3( 0.5f,  0.5f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f))); // top right
			vertices.push_back(Vertex(glm::vec3( 0.5f, -0.5f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f))); // bottom right
			vertices.push_back(Vertex(glm::vec3(-0.5f, -0.5f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f))); // bottom left
			vertices.push_back(Vertex(glm::vec3(-0.5f,  0.5f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f))); // top left
			indices.push_back(0);
			indices.push_back(1);
			indices.push_back(3);
			indices.push_back(1);
			indices.push_back(2);
			indices.push_back(3);
			handle = renderer.generateVBO(ShaderPrograms::DEFAULT, vertices, indices);

			delta_vec = glm::vec3(glm::circularRand(1.0), 0.0);
		}
		template<typename Renderer>
		void draw(Renderer& renderer, double& fps) {
//			LOG_D("Starting DVD render");
			renderer.bindTexture(ShaderPrograms::DEFAULT, "texture_diffuse0", dvd_texture, 0);
			// create transformations
			glm::mat4 projection = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

			projection = glm::translate(projection, translate_vec);
			projection = glm::scale(projection, 0.5f / glm::vec3(scale, 1.0));

			glm::vec3 right_surface = glm::vec3(1.0, 0.0, 0.0);
			glm::vec3 left_surface = glm::vec3(1.0, 0.0, 0.0);
			glm::vec3 top_surface = glm::vec3(0.0, 1.0, 0.0);
			glm::vec3 bottom_surface = glm::vec3(0.0, 1.0, 0.0);

			right_surface += glm::vec3(glm::diskRand(0.05f), 0.0f);
			left_surface += glm::vec3(glm::diskRand(0.05f), 0.0f);
			top_surface += glm::vec3(glm::diskRand(0.05f), 0.0f);
			bottom_surface += glm::vec3(glm::diskRand(0.05f), 0.0f);

			glm::dvec2 offset = (scale - glm::dvec2(0.235, 0.115)) / scale;

			glm::vec3 scale_factor = glm::vec3(speed / (scale * fps * 4.0), 0.0);
			double length = glm::length(delta_vec * scale_factor);

			bool reflected = false;
			if(isAtWindowEdge(RIGHT, length, offset)) {
				delta_vec = glm::normalize(glm::reflect(delta_vec, right_surface));
				translate_vec.x =  offset.x - length;
				reflected = true;
			} if(isAtWindowEdge(LEFT, length, offset)) {
				delta_vec = glm::normalize(glm::reflect(delta_vec, left_surface));
				translate_vec.x = -offset.x + length;
				reflected = true;
			} if(isAtWindowEdge(TOP, length, offset)) {
				delta_vec = glm::normalize(glm::reflect(delta_vec, top_surface));
				translate_vec.y =  offset.y - length;
				reflected = true;
			} if(isAtWindowEdge(BOTTOM, length, offset)) {
				delta_vec = glm::normalize(glm::reflect(delta_vec, bottom_surface));
				translate_vec.y = -offset.y + length;
				reflected = true;
			}
			if(reflected) {
				updateLogoColor();
			}
			translate_vec += delta_vec * scale_factor;

			renderer.setColor(ShaderPrograms::DEFAULT, logo_color);
			renderer.setMatrices(ShaderPrograms::DEFAULT, glm::mat4(1), glm::mat4(1), projection);

			renderer.render(handle, _3D::Primitive::TRIANGLES);
//			LOG_D("Finished DVD render");
		}

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
		cmrc::embedded_filesystem fs = cmrc::DVD::get_filesystem();

		glm::vec3 logo_color = glm::vec3(1.0, 1.0, 1.0);

		_3D::Texture dvd_texture;
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		VBO_handle handle;

		glm::vec3 translate_vec = glm::vec3(0.0);
		glm::vec3 delta_vec = glm::normalize(glm::vec3(1.0, 1.0, 0.0));

		glm::dvec2 scale = glm::dvec2(1.0,1.0);
		double speed = 1.0;
};

} /* namespace DVD */


#endif /* SAMPLES_DVD_SRC_DVD_HPP_ */
