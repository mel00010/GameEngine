/******************************************************************************
 * GameCore.hpp
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
#ifndef SRC_GAMECORE_HPP_
#define SRC_GAMECORE_HPP_

#include "CallbackHandler.hpp"

#include <2D/FPSRenderer.hpp>
#include <2D/TextRenderer.hpp>

#include <3D/Texture.hpp>

#include <GL/GL.hpp>
#include <GL/Program.hpp>
#include <GL/WindowManager.hpp>

#include <Util/Singleton.hpp>

#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <array>
#include <functional>
#include <limits>
#include <list>
#include <map>



namespace GameEngine {

class GameCoreConcrete : public CallbackHandler, public GL::WindowManager, public _2D::FPSRenderer {
	protected:
		void preSetup();
		void postSetup();

		void preTick();
		void postTick();

		void preRender();
		void postRender();

		void loop();

		void initSDL();
		void initGL();
		void initFreeType();

		void registerDefaultCallbacks();

		void setProgramName(std::string name);

	protected:
		std::string program_name;
		GL::GL gl;
		GL::ProgramRef p;
};

template <typename Derived> class GameCore : public GameCoreConcrete, public Singleton<Derived> {
	public:
		void runLoop() {
			setup();
			loop();
		}

	private:
		/**** Convenience method for CRTP ****/
		Derived& derived() {
			return *static_cast<Derived*>(this);
		}
		void setup() {
			setProgramName(derived().program_name);
			registerTimeoutCallback("tick", ms_per_tick, [&]() { tick(); } , true);
			registerTimeoutCallback("render", 0, [&]() { render(); }, true);

			preSetup();
			derived().registerCallbacks();
			derived().setup();
			postSetup();
		}
		void render() {
			preRender();
			derived().render();
			postRender();
		}
		void tick() {
			preTick();
			derived().tick();
			postTick();
		}
};


} /* namespace GameEngine */

#include "GameCore.tpp"

#endif /* SRC_GAMECORE_HPP_ */
