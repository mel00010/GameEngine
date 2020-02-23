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

namespace game_engine {
namespace Sound {

Music::~Music() noexcept {
	if(music_ == nullptr) {
		return;
	}
	// Do not call SDL_Mix functions if Mix is not initialized
	if(!Mix_Init(0)) {
		return;
	}
	Mix_FreeMusic(music_);
}

Mix_Music* Music::LoadMusic(const cmrc::file file) {
	std::vector<uint8_t> file_contents(file.begin(), file.end());
	path_ = file.path();
	music_ = Mix_LoadMUS_RW(SDL_RWFromMem(file_contents.data(), file_contents.size()), 1);
	if (music_ == nullptr) {
		LOG_E("Mix_LoadMUS:  " << Mix_GetError());
	}
	return music_;
}

void Music::Play(const size_t times) {
	if(times == 0) {
		return;
	}
	if (Mix_PlayMusic(music_, static_cast<int>(times - 1)) == -1) {
		LOG_E("Mix_PlayMusic:  " << Mix_GetError());
	}
}

void Music::Pause() {
	Mix_PauseMusic();
}
void Music::Resume() {
	Mix_ResumeMusic();
}
void Music::Halt() {
	Mix_HaltMusic();
}
int Music::SetVolume(const int volume) {
	if(volume < -1) {
		return -1;
	}
	return Mix_VolumeMusic(volume);
}
bool Music::IsPaused() {
	return Mix_PausedMusic();
}
bool Music::IsPlaying() {
	return Mix_PlayingMusic();
}
} /* namespace Sound */
} /* namespace game_engine */


