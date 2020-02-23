/******************************************************************************
 * SlangTest.cpp
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

#include "SlangTest.hpp"

#include <3D/Model.hpp>
#include <GL/Shader.hpp>
#include <GL/ShaderProgram.hpp>

#include <cmrc/cmrc.hpp>
#include <glm/glm.hpp>
#include <Log.hpp>
#include <slang.h>

#include <thread>

using namespace game_engine;

namespace slang_test {

void SlangTest::RegisterCallbacks() {
	RegisterKeyboardEventCallback(SDL_SCANCODE_O, KeyEventType::DOWN, [this](SDL_KeyboardEvent&) {
		oof_.Play();
	});
	RegisterKeyboardEventCallback(SDL_SCANCODE_P, KeyEventType::DOWN, [this](SDL_KeyboardEvent&) {
		ouch_.Play();
	});
	RegisterKeyboardEventCallback(SDL_SCANCODE_R, KeyEventType::DOWN, [this](SDL_KeyboardEvent&) {
		rickroll_.Play();
	});
	RegisterKeyboardEventCallback(SDL_SCANCODE_T, KeyEventType::DOWN, [this](SDL_KeyboardEvent&) {
		rickroll_.Pause();
	});
	RegisterKeyboardEventCallback(SDL_SCANCODE_Y, KeyEventType::DOWN, [this](SDL_KeyboardEvent&) {
		rickroll_.Resume();
	});
	RegisterTimeoutCallback("ms_per_frame", 1000, [this]() {
		LOG_D("ms/frame = " << frame_time_ms_ << " | fps = " << fps_avg_);
	}, true);
}

void SlangTest::Setup() {
	oof_ = Sound::Sound(fs_.open("oof.ogg"));
	ouch_ = Sound::Sound(fs_.open("ouch.ogg"));
	rickroll_ = Sound::Music(fs_.open("rickroll.ogg"));


}

void SlangTest::Render() {

}

void SlangTest::Tick() {

}

} /* namespace slang_test */



