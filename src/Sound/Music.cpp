/******************************************************************************
 * Music.cpp
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

#include "Music.hpp"

#include <Log.hpp>

namespace Sound {

Music::~Music() {
	if(music == nullptr) {
		return;
	}
	// Do not call SDL_Mix functions if Mix is not initialized
	if(!Mix_Init(0)) {
		return;
	}
	Mix_FreeMusic(music);
}

Mix_Music* Music::loadMusic(const std::string file_path) {
	music = Mix_LoadMUS(file_path.c_str());
	if (music == nullptr) {
		LOG_E("Mix_LoadMUS:  " << Mix_GetError());
	}
	return music;
}

void Music::play(size_t times) {
	if(times == 0) {
		return;
	}
	if (Mix_PlayMusic(music, static_cast<int>(times - 1)) == -1) {
		LOG_E("Mix_PlayMusic:  " << Mix_GetError());
	}
}

void Music::pause() {
	Mix_PauseMusic();
}
void Music::resume() {
	Mix_ResumeMusic();
}
void Music::halt() {
	Mix_HaltMusic();
}
int Music::setVolume(int volume) {
	if(volume < -1) {
		return -1;
	}
	return Mix_VolumeMusic(volume);
}
bool Music::isPaused() {
	return Mix_PausedMusic();
}
bool Music::isPlaying() {
	return Mix_PlayingMusic();
}
} /* namespace Sound */



