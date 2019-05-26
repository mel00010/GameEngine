/******************************************************************************
 * DVDcpp
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

//#define GLM_FORCE_SWIZZLE

#include "DVDCore.hpp"

#include <GL/Attribute.hpp>
#include <GL/Shader.hpp>

#include <Log.hpp>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtx/color_space.hpp>

#include <Resources.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <algorithm>
#include <functional>

#include <GameCore.hpp>

using namespace GameEngine;

namespace DVD {

void DVDCore::registerCallbacks() {
	registerKeyboardEventCallback(SDL_SCANCODE_R,			KeyEventType::DOWN, [this](SDL_KeyboardEvent&) { this->reset(); });
	registerKeyboardEventCallback(SDL_SCANCODE_A,			KeyEventType::DOWN, [this](SDL_KeyboardEvent&) { addDVD(); });
	registerKeyboardEventCallback(SDL_SCANCODE_D,			KeyEventType::DOWN, [this](SDL_KeyboardEvent&) { removeDVD(); });
	registerKeyboardEventCallback(SDL_SCANCODE_PAGEUP,		KeyEventType::HELD, [this]() { scroll_factor *= 1.0 + (0.0525/scroll_factor); });
	registerKeyboardEventCallback(SDL_SCANCODE_PAGEDOWN,	KeyEventType::HELD, [this]() { scroll_factor *= 1.0 - (scroll_factor/18.095); });

	registerMouseWheelEventCallback([this](glm::ivec2 delta) {
		size_t curr_time = SDL_GetTicks();
		modifySpeed(static_cast<double>(delta.y) * scroll_factor * 0.1);
		if((curr_time > prev_time + 10) || counter == 10) {
			prev_time = curr_time;
			counter = 0;
		}
		counter++;
	});

	registerWindowEventCallback([this](SDL_WindowEvent& ev) {
		switch(ev.event) {
			case SDL_WINDOWEVENT_RESIZED:
				setScale(glm::dvec2(ev.data1, ev.data2) / glm::dvec2(1920, 1080));
		}
	});

}

void DVDCore::setup() {
	setSpeed(2.0f);


	p = std::make_shared<GL::Program>();
	p->init();
	GL::ShaderRef vertex_shader = std::make_shared<GL::Shader>(Resources[static_cast<size_t>(ResourceID::VERTEX_SHADER)], GL::ShaderType::VERTEX);
	GL::ShaderRef fragment_shader = std::make_shared<GL::Shader>(Resources[static_cast<size_t>(ResourceID::FRAGMENT_SHADER)], GL::ShaderType::FRAGMENT);
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

	glUseProgram(p->getPH());
	addDVD();
}

void DVDCore::render() {
	for(auto& i : dvds) {
		i.draw(fps);
	}
}

void DVDCore::tick() {

}

} /* namespace DVD */

