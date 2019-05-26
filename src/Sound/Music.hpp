/******************************************************************************
 * Music.hpp
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
#ifndef SRC_SOUND_MUSIC_HPP_
#define SRC_SOUND_MUSIC_HPP_

#include <Util/ResourceDefs.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <string>

namespace Sound {

class Music {
	public:
		Music() {};
		Music(const std::string file_path) {
			loadMusic(file_path);
		}
		template <Enum ResourceID> Music(const Resource<ResourceID> resource) {
			loadMusic(resource);
		}
		~Music();


		template <Enum ResourceID> Mix_Music* loadMusic(const Resource<ResourceID> resource) {
			std::string file_location;
			char *base_path = SDL_GetBasePath();
			if (base_path) {
				file_location = base_path;
			} else {
				file_location = "./";
			}
			file_location += resource.file_path;
			return loadMusic(file_location);
		}

		Mix_Music* loadMusic(const std::string file_path);


	public:
		void play(size_t times = 1);
		void pause();
		void resume();
		void halt();
		int  setVolume(int volume);
		bool isPaused();
		bool isPlaying();


	public:
		std::string path = "";
		Mix_Music* music = nullptr;
};

} /* namespace Sound */




#endif /* SRC_SOUND_MUSIC_HPP_ */
