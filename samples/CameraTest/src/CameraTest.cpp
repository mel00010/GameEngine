/******************************************************************************
 * CameraTest.cpp
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

#include "CameraTest.hpp"

#include <Log.hpp>

#include <3D/Model.hpp>
#include <3D/Skybox.hpp>

#include <GL/Shader.hpp>
#include <GL/ShaderProgram.hpp>

#include <cmrc/cmrc.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>

#include <gflags/gflags.h>

DEFINE_bool(test_bool, false, "Test bool");

using namespace game_engine;

namespace camera_test {

void CameraTest::RegisterCallbacks() {
	RegisterKeyboardEventCallback(SDL_SCANCODE_W, KeyEventType::HELD, [this]() {
		glm::vec3 dir { camera_.camera_front_ };
		dir.y = 0.0f;
		dir *= kCameraMoveMultiplier;
		camera_.MoveCamera(dir);
	});
	RegisterKeyboardEventCallback(SDL_SCANCODE_A, KeyEventType::HELD, [this]() {
		glm::vec3 dir { -glm::normalize(glm::cross(camera_.camera_front_, camera_.camera_up_)) };
		dir.y = 0.0f;
		dir *= kCameraMoveMultiplier;
		camera_.MoveCamera(dir);
	});
	RegisterKeyboardEventCallback(SDL_SCANCODE_S, KeyEventType::HELD, [this]() {
		glm::vec3 dir { -camera_.camera_front_ };
		dir.y = 0.0f;
		dir *= kCameraMoveMultiplier;
		camera_.MoveCamera(dir);
	});
	RegisterKeyboardEventCallback(SDL_SCANCODE_D, KeyEventType::HELD, [this]() {
		glm::vec3 dir { glm::normalize(glm::cross(camera_.camera_front_, camera_.camera_up_)) };
		dir.y = 0.0f;
		dir *= kCameraMoveMultiplier;
		camera_.MoveCamera(dir);
	});
	RegisterKeyboardEventCallback(SDL_SCANCODE_SPACE, KeyEventType::HELD, [this]() {
		glm::vec3 dir { camera_.camera_up_ };
		dir *= kCameraVertMoveMultiplier;
		camera_.MoveCamera(dir);
	});
	RegisterKeyboardEventCallback(SDL_SCANCODE_LSHIFT, KeyEventType::HELD, [this]() {
		glm::vec3 dir { -camera_.camera_up_ };
		dir *= kCameraVertMoveMultiplier;
		camera_.MoveCamera(dir);
	});
	RegisterKeyboardEventCallback(SDL_SCANCODE_RSHIFT, KeyEventType::HELD, [this]() {
		glm::vec3 dir { -camera_.camera_up_ };
		dir *= kCameraVertMoveMultiplier;
		camera_.MoveCamera(dir);
	});
	RegisterMouseMotionEventCallback([this](SDL_MouseMotionEvent&, glm::ivec2 /* pos */, glm::ivec2 delta) {
		if(renderer_.IsCursorDisabled()) {
			camera_.RotateCamera(static_cast<double>(delta.x)/kCameraRotationFactor,
					-static_cast<double>(delta.y)/kCameraRotationFactor);
		}
	});
	RegisterWindowEventCallback([this](SDL_WindowEvent& ev) {
		switch(ev.event) {
			case SDL_WINDOWEVENT_RESIZED:
				camera_.UpdateProjection(glm::ivec2(ev.data1, ev.data2));
		}
	});
	RegisterTimeoutCallback("ms_per_frame", kFrameDebugPrintIntervalMs, [this]() {
		LOG_D("ms/frame = " << frame_time_ms_ << " | fps = " << fps_avg_);
	}, true);
	RegisterKeyboardEventCallback(SDL_SCANCODE_O, KeyEventType::DOWN, [this](SDL_KeyboardEvent&) {
		nanosuits_.push_back(_3D::Model(renderer_, fs_, "nanosuit"));
		nanosuits_.back().Move(glm::ballRand(kNanosuitMoveRandRadius));
		nanosuits_.back().Scale(kNanosuitScale);
	});
}


void CameraTest::Setup() {
	cube_ = _3D::Model(renderer_, fs_, "cube");
	cube_.Move(kCubePosition);
	cube_.Scale(kCubeScale);

	axes_ = _3D::Model(renderer_, fs_, "axes");
	axes_.Scale(kAxesScale);

	nanosuits_.push_back(_3D::Model(renderer_, fs_, "nanosuit"));
	nanosuits_.back().Move(glm::vec3(1.0, 0.0, 0.0));
	nanosuits_.back().Scale(kNanosuitScale);

	grid_ = _3D::Model(renderer_, fs_, "grid");
	grid_.Rotate(kGridRotation);

	camera_.Init(renderer_.GetWindowSize());

	skybox_ = _3D::Skybox(renderer_, fs_, "nebula");
}

void CameraTest::Render() {
	camera_.DrawModel(renderer_, skybox_, ShaderPrograms::SKYBOX);

	cube_.Rotate(kCubeRotation);
	renderer_.SetColor(ShaderPrograms::DEFAULT, kCubeColor);
	camera_.DrawModel(renderer_, cube_, ShaderPrograms::DEFAULT);

	renderer_.SetColor(ShaderPrograms::DEFAULT, kGridColor);
	camera_.DrawModel(renderer_, grid_, ShaderPrograms::DEFAULT);

	renderer_.SetColor(ShaderPrograms::DEFAULT, kNanosuitColor);
	for(auto& i : nanosuits_) {
		camera_.DrawModel(renderer_, i, ShaderPrograms::DEFAULT);
	}
	renderer_.DisableDepthTesting();

	const glm::mat4 view { camera_.view_ };
	const glm::mat4 projection { camera_.projection_ };

	camera_.view_ = glm::mat4(glm::mat3(view));
	camera_.projection_ = glm::mat4(1.0);

	renderer_.SetColor(ShaderPrograms::DEFAULT, kAxesColor);
	camera_.DrawModel(renderer_, axes_, ShaderPrograms::DEFAULT);

	camera_.view_ = view;
	camera_.projection_ = projection;
	renderer_.EnableDepthTesting();
}

void CameraTest::Tick() {

}

} /* namespace CameraTest */
