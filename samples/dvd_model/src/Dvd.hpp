/******************************************************************************
 * Dvd.hpp
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


#include <Util/Uuid.hpp>
#include <Log.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <GL/glew.h>

#include <cmrc/cmrc.hpp>

CMRC_DECLARE(dvd);

using namespace game_engine;

namespace dvd {

class Dvd {
	public:
		template<typename Renderer> Dvd(Renderer& renderer) {
			dvd_ = _3D::Model(renderer, fs_, "dvd");

			glm::ivec2 size = renderer.GetWindowSize();
			projection_ = glm::ortho(0.0f, static_cast<float>(size.x), 0.0f, static_cast<float>(size.y));

			UpdateLogoColor();
			delta_vec_ = glm::vec3(glm::circularRand(1.0), 0.0);

			dvd_.ScaleXY(0.5f/scale_);
		}

		void CalculateMovement(float fps);

		template<typename Renderer>
		void Draw(Renderer& renderer, float fps) {
			CalculateMovement(fps);
			renderer.SetColor(ShaderPrograms::DEFAULT, logo_color_);
			renderer.SetMatrices(ShaderPrograms::DEFAULT, dvd_.model_, view_, projection_);
			dvd_.Draw(renderer);
		}

		void SetScale(glm::dvec2 _scale);
		void SetSpeed(float _speed = 1.0);
		void ModifySpeed(float delta = 0.0);
		double GetSpeed();
		void Reset();

	protected:
		enum class WindowEdge : std::uint8_t {
			TOP,
			BOTTOM,
			LEFT,
			RIGHT
		};
		bool IsAtWindowEdge(WindowEdge edge, float length, glm::vec2 offset);
		void UpdateLogoColor();

	protected:
		cmrc::embedded_filesystem fs_ = cmrc::dvd::get_filesystem();

		glm::vec3 logo_color_ = glm::vec3(1.0, 1.0, 1.0);

		_3D::Texture dvd_texture_;
		_3D::Model dvd_;
		glm::mat4 view_			= glm::mat4(1.0f);
		glm::mat4 projection_	= glm::mat4(1.0f);
		VboHandle handle_;

		glm::vec3 delta_vec_ = glm::normalize(glm::vec3(1.0, 1.0, 0.0));

		glm::vec2 scale_ = glm::vec2(1.0,1.0);
		float speed_ = 1.0;
};

} /* namespace dvd */


#endif /* SAMPLES_DVD_SRC_DVD_HPP_ */
