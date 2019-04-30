/******************************************************************************
 * DVDCore.hpp
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
#ifndef SAMPLES_DVD_SRC_DVDCORE_HPP_
#define SAMPLES_DVD_SRC_DVDCORE_HPP_

#include "DVD.hpp"

#include <GameCore.hpp>

namespace DVD {

class DVDCore : public GameEngine::GameCore<DVDCore> {
	public:
		void setScale(glm::dvec2 scale) {
			for(auto& i : dvds) {
				i.setScale(scale);
			}
		}

		void setSpeed(double speed = 1.0) {
			for(auto& i : dvds) {
				i.setSpeed(speed);
			}
		}
		void modifySpeed(double delta = 0.0) {
			for(auto& i : dvds) {
				i.modifySpeed(delta);
			}
		}
		void reset() {
			for(auto& i : dvds) {
				i.reset();
			}
		}
		void addDVD() {
			dvds.push_back(DVD(p));
		}
		void removeDVD() {
			if(!dvds.empty()) {
				dvds.pop_back();
			}
		}
	public:
		void setup();
		void tick();
		void render();
		void registerCallbacks();
	protected:
		std::list<DVD> dvds;

		double scroll_factor = 1.0;
		size_t counter = 0;
		size_t prev_time = SDL_GetTicks();
};

} /* namespace DVD */

#endif /* SAMPLES_DVD_SRC_DVDCORE_HPP_ */
