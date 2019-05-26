/******************************************************************************
 * Sound.hpp
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
#ifndef SRC_SOUND_SOUND_HPP_
#define SRC_SOUND_SOUND_HPP_

#include <Util/ResourceDefs.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <string>

namespace Sound {

class Sound {
	public:
		Sound() {};
		Sound(const std::string file_path) {
			loadSound(file_path);
		}
		template <Enum ResourceID> Sound(const Resource<ResourceID> resource) {
			loadSound(resource);
		}
		~Sound();


		template <Enum ResourceID> Mix_Chunk* loadSound(const Resource<ResourceID> resource) {
			std::string file_location;
			char *base_path = SDL_GetBasePath();
			if (base_path) {
				file_location = base_path;
			} else {
				file_location = "./";
			}
			file_location += resource.file_path;
			return loadSound(file_location);
		}

		Mix_Chunk* loadSound(const std::string file_path);


	public:
		void play(size_t times = 1);
		int  setVolume(int volume);
	public:
		std::string path = "";
		int channel = -2;
		Mix_Chunk* chunk = nullptr;
};

} /* namespace Sound */


#endif /* SRC_SOUND_SOUND_HPP_ */
