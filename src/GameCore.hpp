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
#include "FPSRenderer.hpp"
#include "GL.hpp"
#include "Program.hpp"
#include "TextRenderer.hpp"
#include "Texture.hpp"
#include "WindowManager.hpp"

#include "Util/Singleton.hpp"

#include <array>
#include <functional>
#include <limits>
#include <list>
#include <map>

#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>



namespace GameEngine {

class GameCoreConcrete : public CallbackHandler, public WindowManager, public FPSRenderer {
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

	protected:
		GL gl;
		ProgramRef p;
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
