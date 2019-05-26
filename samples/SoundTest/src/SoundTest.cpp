/******************************************************************************
 * SoundTest.cpp
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

#include "SoundTest.hpp"

#include <Log.hpp>

#include <3D/Model.hpp>

#include <GL/Program.hpp>
#include <GL/Shader.hpp>

#include <Resources.hpp>

#include <glm/glm.hpp>

#include <thread>

using namespace GameEngine;

namespace SoundTest {

void SoundTest::registerCallbacks() {
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
	registerKeyboardEventCallback(SDL_SCANCODE_O, KeyEventType::DOWN, [this](SDL_KeyboardEvent&) {
		oof.play();
	});
	registerKeyboardEventCallback(SDL_SCANCODE_P, KeyEventType::DOWN, [this](SDL_KeyboardEvent&) {
		ouch.play();
	});
	registerKeyboardEventCallback(SDL_SCANCODE_R, KeyEventType::DOWN, [this](SDL_KeyboardEvent&) {
		rickroll.play();
	});
	registerKeyboardEventCallback(SDL_SCANCODE_T, KeyEventType::DOWN, [this](SDL_KeyboardEvent&) {
		rickroll.pause();
	});
	registerKeyboardEventCallback(SDL_SCANCODE_Y, KeyEventType::DOWN, [this](SDL_KeyboardEvent&) {
		rickroll.resume();
	});

	registerMouseMotionEventCallback([this](SDL_MouseMotionEvent&, glm::ivec2 /* pos */, glm::ivec2 delta) {
		if(isCursorDisabled()) {
			camera.rotateCamera(static_cast<double>(delta.x)/10, -static_cast<double>(delta.y)/10);
		}
	});
	registerWindowEventCallback([this](SDL_WindowEvent& ev) {
		switch(ev.event) {
			case SDL_WINDOWEVENT_RESIZED:
				camera.updateProjection();
		}
	});
	registerTimeoutCallback("ms_per_frame", 1000, [this]() {
		LOG_D("ms/frame = " << frame_time_ms << " | fps = " << fps_avg);
	}, true);
}


void SoundTest::setup() {
	p = std::make_shared<GL::Program>();
	p->init();
	GL::ShaderRef vertex_shader = std::make_shared<GL::Shader>(getResource(ResourceID::VERTEX_SHADER), GL::ShaderType::VERTEX);
	GL::ShaderRef fragment_shader = std::make_shared<GL::Shader>(getResource(ResourceID::FRAGMENT_SHADER), GL::ShaderType::FRAGMENT);
	vertex_shader->init();
	fragment_shader->init();
	p->attachShader(vertex_shader);
	p->attachShader(fragment_shader);
	p->link();

	/* When all init functions run without errors,
	   the glsl_program can initialize the resources */
	if (!p->isValid()) {
		throw EXIT_FAILURE;
	}
	p->useProgram();
	gl.bind();

	grid = _3D::Model(getResource(ResourceID::GRID));
	grid.rotate(glm::vec3(glm::radians(91.0f), glm::radians(90.0f), glm::radians(0.0f)));

	camera.init(getWindow(), p);

	oof = Sound::Sound(getResource(ResourceID::OOF));
	ouch = Sound::Sound(getResource(ResourceID::OUCH));
	rickroll = Sound::Music(getResource(ResourceID::RICKROLL));
}

void SoundTest::render() {
	p->use();
	gl.bind();

	p->setVec3("color", line_color);
	camera.drawModel(grid, p);
}

void SoundTest::tick() {

}

} /* namespace SoundTest */


