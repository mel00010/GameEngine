/******************************************************************************
 * Camera.hpp
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
#ifndef SRC_CAMERA_HPP_
#define SRC_CAMERA_HPP_

#include "Model.hpp"

#include <Log.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <SDL2/SDL.h>

namespace GameEngine {

class Camera {
	public:
		void init(SDL_Window* _window, ProgramRef _p) {
			window = _window;
			p = _p;
			fov = 45.0f;
			updateView();
			updateProjection();
			valid = true;
		}

		void setCameraRotation(glm::vec3 rotation) {
			cameraFront = glm::normalize(rotation);
			updateView();
		}
		void setCameraPos(glm::vec3 pos) {
			cameraPos = pos;
			updateView();
		}
		void rotateCamera(double _yaw, double _pitch) {
			yaw += _yaw;
			pitch += _pitch;

			glm::vec3 direction;
			direction.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
			direction.y = sin(glm::radians(pitch));
			direction.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
			cameraFront = glm::normalize(direction);
			updateView();
		}
		void moveCamera(glm::vec3 delta) {
			cameraPos += delta;
			updateView();
		}
		void setFOV(float _fov) {
			fov = _fov;
			updateProjection();
		}
		void updateView() {
			view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		}
		void updateProjection() {
			int x, y;
			SDL_GetWindowSize(window, &x, &y);
			projection = glm::perspective(glm::radians(fov), static_cast<float>(x) / static_cast<float>(y), 0.1f, 100.0f);
		}

		void drawModel(Model& model, ProgramRef prog) {
			// retrieve the matrix uniform locations
			unsigned int modelLoc		= glGetUniformLocation(p->getPH(), "model");
			unsigned int viewLoc		= glGetUniformLocation(p->getPH(), "view");
			unsigned int projectionLoc	= glGetUniformLocation(p->getPH(), "projection");

			// pass them to the shaders (3 different ways)
			glUniformMatrix4fv(modelLoc,		1, GL_FALSE, &model.model[0][0]);
			glUniformMatrix4fv(viewLoc, 		1, GL_FALSE, &view[0][0]);
			glUniformMatrix4fv(projectionLoc,	1, GL_FALSE, &projection[0][0]);
			model.draw(prog);
		}

		SDL_Window* window;
		ProgramRef p = nullptr;
		float fov;
		double cameraSpeed = 0.01;
		double yaw = 0.0;
		double pitch = 15.0;

		glm::vec3 cameraPos = glm::vec3(0.0f, 0.5f, 3.0f);
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f,  0.0f);

		glm::mat4 view			= glm::mat4(1.0f);
		glm::mat4 projection	= glm::mat4(1.0f);

		bool valid = false;
};

} /* namespace GameEngine */




#endif /* SRC_CAMERA_HPP_ */
