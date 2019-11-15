/******************************************************************************
 * WindowManager.hpp
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
#ifndef SRC_WINDOWMANAGER_HPP_
#define SRC_WINDOWMANAGER_HPP_


#include <glm/glm.hpp>
#include <string>

namespace GameEngine {

template <typename Derived> class WindowManager {
	public:
		void init(std::string program_name) {
			derived().init(program_name);
		}
		static glm::ivec2 getWindowSize() {
			return Derived::getWindowSize();
		}

		void setFullscreen(bool enable = false) {
			derived().setFullscreen(enable);
		}
		bool isFullscreen() {
			return derived().isFullscreen();
		}
		void toggleFullscreen() {
			derived().toggleFullscreen();
		}

		void setVSyncEnabled(bool enable = false) {
			derived().setVSyncEnabled(enable);
		}
		bool isVSyncEnabled() {
			return derived().isVSyncEnabled();
		}
		void enableVSync() {
			derived().enableVSync();
		}
		void disableVSync() {
			derived().disableVSync();
		}
		void toggleVSync() {
			derived().toggleVSync();
		}

		void quit() {
			derived().quit();
		}
		bool isCursorDisabled() {
			return derived().isCursorDisabled();
		}
		void disableCursor(bool disabled = true) {
			derived().disableCursor(disabled);
		}
		bool toggleCursor() {
			return derived().toggleCursor();
		}

		void redrawWindowBounds(glm::ivec2 size) {
			derived().redrawWindowBounds(size);
		}
	private:
		/**** Convenience method for CRTP ****/
		inline Derived& derived() {
			return *static_cast<Derived*>(this);
		}
};


} /* namespace GameEngine */

#include "WindowManager.tpp"

#endif /* SRC_WINDOWMANAGER_HPP_ */
