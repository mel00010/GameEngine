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

#include "Dvd.hpp"

#include <GameCore.hpp>

namespace dvd {

class DvdCore : public game_engine::GameCore<DvdCore> {
	public:
		static constexpr std::string_view program_name_ = "DVD";
		void Setup();
		void Tick();
		void Render();
		void RegisterCallbacks();

	public:
		void SetScale(glm::dvec2 scale) {
			for(auto& i : dvds_) {
				i.SetScale(scale);
			}
		}

		void SetSpeed(double speed = 1.0) {
			for(auto& i : dvds_) {
				i.SetSpeed(speed);
			}
		}
		void ModifySpeed(double delta = 0.0) {
			for(auto& i : dvds_) {
				i.ModifySpeed(delta);
			}
		}
		void Reset() {
			for(auto& i : dvds_) {
				i.Reset();
			}
		}
		void AddDvd() {
			dvds_.push_back(Dvd(renderer_));
		}
		void RemoveDvd() {
			if(!dvds_.empty()) {
				dvds_.pop_back();
			}
		}

	protected:
		std::list<Dvd> dvds_;

		double scroll_factor_ = 1.0;
		size_t counter_ = 0;
		size_t prev_time_ = SDL_GetTicks();
};

} /* namespace dvd */

#endif /* SAMPLES_DVD_SRC_DVDCORE_HPP_ */
