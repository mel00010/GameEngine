/*****************************************************************************
 * Sound.cpp
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

#include "Sound.hpp"

#include <Log.hpp>

#include <string>

namespace game_engine {
namespace Sound {

Sound::~Sound() {
	if(chunk_ == nullptr) {
		return;
	}
	// Do not call SDL_Mix functions if Mix is not initialized
	if(!Mix_Init(0)) {
		return;
	}
	if(channel_ != -2) {
		if (Mix_Playing(channel_) != 0) {
			// If the chunk is playing, do not free it as it will cause "problems"
			if(Mix_GetChunk(channel_) == chunk_) {
				return;
			}
		}
	}
	Mix_FreeChunk(chunk_);
}

Mix_Chunk* Sound::LoadSound(const cmrc::file file) {
	std::vector<uint8_t> file_contents(file.begin(), file.end());
	path_ = file.path();
	/* Allocate one more channel */
	Mix_AllocateChannels(Mix_AllocateChannels(-1) + 1);
	chunk_ = Mix_LoadWAV_RW(SDL_RWFromMem(file_contents.data(), file_contents.size()), 1);
	if (chunk_ == nullptr) {
		LOG_E("Mix_LoadWav:  " << Mix_GetError());
	}
	return chunk_;
}

void Sound::Play(const size_t times) {
	if(times == 0) {
		return;
	}
	if((channel_ = Mix_PlayChannel(-1, chunk_, static_cast<int>(times - 1))) == -1) {
		LOG_E("Mix_PlayChannel:  " << Mix_GetError());
	}
}

int Sound::SetVolume(const int volume) {
	return Mix_VolumeChunk(chunk_, volume);
}
} /* namespace Sound */
} /* namespace game_engine */

