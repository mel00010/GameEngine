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

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <cmrc/cmrc.hpp>

#include <string>

namespace GameEngine {
namespace Sound {

class Music {
	public:
		Music() {};
		Music(const cmrc::file file) {
			loadMusic(file);
		}
		~Music();

		Mix_Music* loadMusic(const cmrc::file file);


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
} /* namespace GameEngine */



#endif /* SRC_SOUND_MUSIC_HPP_ */
