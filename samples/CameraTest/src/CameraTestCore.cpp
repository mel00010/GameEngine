/******************************************************************************
 * CameraTestCore.cpp
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

#include "CameraTestCore.hpp"

#include <Log.hpp>

#include <3D/Model.hpp>
#include <3D/Skybox.hpp>

#include <GL/Shader.hpp>
#include <GL/ShaderProgram.hpp>

#include <cmrc/cmrc.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>


using namespace GameEngine;

namespace CameraTest {

void CameraTestCore::registerCallbacks() {
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
	registerKeyboardEventCallback(SDL_SCANCODE_O, KeyEventType::DOWN, [this](SDL_KeyboardEvent&) {
		nanosuits.push_back(_3D::Model(renderer, fs, "nanosuit"));
		nanosuits.back().move(glm::ballRand(5.0f));
		nanosuits.back().scale(0.05);
	});
}


void CameraTestCore::setup() {
	cube = _3D::Model(renderer, fs, "cube");
	cube.move(glm::vec3(0.0, 0.5, 0.0));
	cube.scale(0.25);

	axes = _3D::Model(renderer, fs, "axes");
	axes.scale(0.1);

	nanosuits.push_back(_3D::Model(renderer, fs, "nanosuit"));
	nanosuits.back().move(glm::vec3(1.0, 0.0, 0.0));
	nanosuits.back().scale(0.05);

	grid = _3D::Model(renderer, fs, "grid");
	grid.rotate(glm::vec3(glm::radians(91.0f), glm::radians(90.0f), glm::radians(0.0f)));

	camera.init(renderer.getWindowSize());

	skybox = _3D::Skybox(renderer, fs, "nebula");
}

void CameraTestCore::render() {
	camera.drawModel(renderer, skybox, ShaderPrograms::SKYBOX);

	cube.rotate(glm::vec3(glm::radians(0.1f), glm::radians(0.2f), glm::radians(-0.3f)));
	renderer.setColor(ShaderPrograms::DEFAULT, glm::vec4(cube_color, 1.0f));
	camera.drawModel(renderer, cube, ShaderPrograms::DEFAULT);
	renderer.setColor(ShaderPrograms::DEFAULT, glm::vec4(line_color, 1.0f));
	camera.drawModel(renderer, grid, ShaderPrograms::DEFAULT);
	renderer.setColor(ShaderPrograms::DEFAULT, glm::vec4(nanosuit_color, 1.0f));
	for(auto& i : nanosuits) {
		camera.drawModel(renderer, i, ShaderPrograms::DEFAULT);
	}
	renderer.disable_depth_testing();

	glm::mat4 view = camera.view;
	glm::mat4 projection = camera.projection;

	camera.view = glm::mat4(glm::mat3(view));
	camera.projection = glm::mat4(1.0);

	renderer.setColor(ShaderPrograms::DEFAULT, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	camera.drawModel(renderer, axes, ShaderPrograms::DEFAULT);

	camera.view = view;
	camera.projection = projection;
	renderer.enable_depth_testing();
}

void CameraTestCore::tick() {

}

} /* namespace CameraTest */
