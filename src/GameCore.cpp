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

#include <ft2build.h>
#include FT_FREETYPE_H

#include <algorithm>
#include <functional>
#include <numeric>

namespace GameEngine {

void GameCoreConcrete::preSetup() {
	registerDefaultCallbacks();

	initSDL();
	initGL();
}

void GameCoreConcrete::postSetup() {

}

void GameCoreConcrete::preTick() {

}
void GameCoreConcrete::postTick() {
	calculateFPS();
	dispatchCallbacks();
}

void GameCoreConcrete::preRender() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	incrementFrameCount();
}
void GameCoreConcrete::postRender() {
	renderFPS();
	SDL_GL_SwapWindow(getWindow());
}


void GameCoreConcrete::registerDefaultCallbacks() {
	registerQuitEventCallback([](SDL_QuitEvent&) {
		LOG_I("Exiting gracefully");
		SDL_Quit();
		exit(EXIT_SUCCESS);
	});
	registerWindowEventCallback([](SDL_WindowEvent& ev) {
		switch(ev.event) {
			case SDL_WINDOWEVENT_RESIZED:
				glViewport(0, 0, ev.data1, ev.data2);
		}
	});

	registerKeyboardEventCallback(SDL_SCANCODE_Q,   KeyEventType::DOWN, [this](SDL_KeyboardEvent&) { quit(); });
	registerKeyboardEventCallback(SDL_SCANCODE_F,   KeyEventType::DOWN, [this](SDL_KeyboardEvent&) { toggleFPS(); });
	registerKeyboardEventCallback(SDL_SCANCODE_F11, KeyEventType::DOWN, [this](SDL_KeyboardEvent&) { toggleFullscreen(); });
	registerKeyboardEventCallback(SDL_SCANCODE_V,   KeyEventType::DOWN, [this](SDL_KeyboardEvent&) { toggleVSync(); });
	registerKeyboardEventCallback(SDL_SCANCODE_E,   KeyEventType::DOWN, [this](SDL_KeyboardEvent&) { toggleCursor(); });
}

void GameCoreConcrete::loop() {
	for(;;) {
		dispatchTimeoutEvents();
	}
}



void GameCoreConcrete::initSDL() {
	/* SDL-related initialising functions */
	SDL_Init(SDL_INIT_VIDEO);
	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	if( !( IMG_Init( flags ) & flags ) ) {
		LOG_F( "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() );
		throw EXIT_FAILURE;
	}

	// Request an OpenGL 4.5 context (should be core)
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

	// Also request a depth buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	setWindow(SDL_CreateWindow("DVD",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1920, 1080,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL));
	SDL_GL_CreateContext(getWindow());
	enableVSync();
}

void GameCoreConcrete::initGL() {
	/* Extension wrangler initialising */
	glewExperimental = GL_TRUE;
	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK) {
		LOG_F("Error: glewInit: " << glewGetErrorString(glew_status));
		throw EXIT_FAILURE;
	}
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	text.init(getWindow());
}



} /* namespace GameEngine */
