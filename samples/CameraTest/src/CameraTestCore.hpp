/******************************************************************************
 * CameraTestCore.hpp
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
#ifndef SAMPLES_CAMERATEST_SRC_CAMERATESTCORE_HPP_
#define SAMPLES_CAMERATEST_SRC_CAMERATESTCORE_HPP_

#include <Camera.hpp>
#include <GameCore.hpp>
#include <Model.hpp>


using namespace GameEngine;

struct Vertex {
		glm::vec3 pos;
		glm::vec2 tex;
		Vertex(glm::vec3 _pos, glm::vec2 _tex) : pos(_pos), tex(_tex) {}
};

class CameraTestCore : public GameEngine::GameCore {
	public:
		/* Make Singleton */
		static CameraTestCore& getInstance() {
			static CameraTestCore instance;
			return instance;
		}

	protected:
		virtual void setup();
		virtual void tick();
		virtual void render();

	protected:
		glm::vec3 line_color = glm::vec3(1.0, 1.0, 0.0);
		glm::vec3 cube_color = glm::vec3(1.0, 1.0, 1.0);

		Camera camera;
		Model<Vertex> cube;
		Model<Vertex> grid;
};


#endif /* SAMPLES_CAMERATEST_SRC_CAMERATESTCORE_HPP_ */
