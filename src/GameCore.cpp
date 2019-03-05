/******************************************************************************
 * GameCore.cpp
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

#include "GameCore.hpp"

#include "Attribute.hpp"
#include "Shader.hpp"

#include <Log.hpp>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace GameEngine {

void GameCore::runLoop() {
	setup();
	LOG_D("Finished setup");
	loop();
}

void GameCore::loop() {
	for(;;) {
		render();
		curr_time = SDL_GetTicks();
		if(curr_time > prev_time + ms_per_tick) {
			prev_time = curr_time;
			tick();
		}
	}
}

SDL_Window* GameCore::getWindow() {
	return window;
}

GameCore::GameCore() : ms_per_tick(50) {}

bool GameCore::isCursorDisabled() {
	return cursor_disabled;
}
void GameCore::disableCursor(bool disabled) {
	cursor_disabled = disabled;
}
bool GameCore::toggleCursor() {
	if(cursor_disabled) {
		cursor_disabled = false;
		SDL_ShowCursor(SDL_ENABLE);
	} else {
		cursor_disabled = true;
		SDL_ShowCursor(SDL_DISABLE);
	}
	return cursor_disabled;
}



} /* namespace GameEngine */
