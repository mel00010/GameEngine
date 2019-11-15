/******************************************************************************
 * CubeTest.cpp
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

#include "CubeTestCore.hpp"

#include <Log.hpp>

#include <3D/Model.hpp>

#include <GL/Shader.hpp>
#include <GL/ShaderProgram.hpp>

#include <cmrc/cmrc.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>


using namespace GameEngine;

namespace CubeTest {

void CubeTestCore::registerCallbacks() {
	registerKeyboardEventCallback(SDL_SCANCODE_W, KeyEventType::HELD, [this]() {
		glm::vec3 dir = camera.cameraFront;
		dir.y = 0.0f;
		dir *= 0.125;
		camera.moveCamera(dir);
	});
	registerKeyboardEventCallback(SDL_SCANCODE_A, KeyEventType::HELD, [this]() {
		glm::vec3 dir = -glm::normalize(glm::cross(camera.cameraFront, camera.cameraUp));
		dir.y = 0.0f;
		dir *= 0.125;
		camera.moveCamera(dir);
	});
	registerKeyboardEventCallback(SDL_SCANCODE_S, KeyEventType::HELD, [this]() {
		glm::vec3 dir = -camera.cameraFront;
		dir.y = 0.0f;
		dir *= 0.125;
		camera.moveCamera(dir);
	});
	registerKeyboardEventCallback(SDL_SCANCODE_D, KeyEventType::HELD, [this]() {
		glm::vec3 dir = glm::normalize(glm::cross(camera.cameraFront, camera.cameraUp));
		dir.y = 0.0f;
		dir *= 0.125;
		camera.moveCamera(dir);
	});
	registerKeyboardEventCallback(SDL_SCANCODE_SPACE, KeyEventType::HELD, [this]() {
		glm::vec3 dir = camera.cameraUp;
		dir *= 0.025;
		camera.moveCamera(dir);
	});
	registerKeyboardEventCallback(SDL_SCANCODE_LSHIFT, KeyEventType::HELD, [this]() {
		glm::vec3 dir = -camera.cameraUp;
		dir *= 0.025;
		camera.moveCamera(dir);
	});
	registerKeyboardEventCallback(SDL_SCANCODE_RSHIFT, KeyEventType::HELD, [this]() {
		glm::vec3 dir = -camera.cameraUp;
		dir *= 0.025;
		camera.moveCamera(dir);
	});
	registerMouseMotionEventCallback([this](SDL_MouseMotionEvent&, glm::ivec2 /* pos */, glm::ivec2 delta) {
		if(renderer.isCursorDisabled()) {
			camera.rotateCamera(static_cast<double>(delta.x)/10, -static_cast<double>(delta.y)/10);
		}
	});
	registerWindowEventCallback([this](SDL_WindowEvent& ev) {
		switch(ev.event) {
			case SDL_WINDOWEVENT_RESIZED:
				camera.updateProjection(glm::ivec2(ev.data1, ev.data2));
		}
	});
	registerTimeoutCallback("ms_per_frame", 1000, [this]() {
		LOG_D("ms/frame = " << frame_time_ms << " | fps = " << fps_avg);
	}, true);
}


void CubeTestCore::setup() {
	cube = _3D::Model(renderer, fs, "cube");
	cube.move(glm::vec3(0.0, 0.5, 0.0));
	cube.scale(0.25);

	camera.init(renderer.getWindowSize());
//	LOG_D(cube);
}

void CubeTestCore::render() {
	cube.rotate(glm::vec3(glm::radians(0.1f), glm::radians(0.2f), glm::radians(-0.3f)));
	renderer.setColor(ShaderPrograms::DEFAULT, glm::vec4(cube_color, 1.0f));
	camera.drawModel(renderer, cube);
}

void CubeTestCore::tick() {

}

} /* namespace CubeTest */
