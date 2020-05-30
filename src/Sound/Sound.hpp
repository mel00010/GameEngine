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

#include <string>
#include <utility>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <cmrc/cmrc.hpp>

#include "LoggerV2/Log.hpp"

namespace game_engine {
namespace sound {

class Sound {
 public:
  Sound& operator=(const Sound& rhs) = default;
  Sound(const Sound& rhs) = default;
  Sound& operator=(Sound&& rhs) noexcept = default;
  Sound(Sound&& rhs) noexcept = default;
  Sound() = default;
  explicit Sound(const cmrc::file file) { LoadSound(file); }
  ~Sound() noexcept;

  Mix_Chunk* LoadSound(const cmrc::file file);

 public:
  void Play(const size_t times = 1);
  int SetVolume(const int volume);

  void swap(Sound& other) noexcept {
    using std::swap;
    swap(other.path_, path_);
    swap(other.channel_, channel_);
    swap(other.chunk_, chunk_);
  }

 public:
  std::string path_ = "";
  int channel_ = -2;
  Mix_Chunk* chunk_ = nullptr;

 private:
  logging::Log log_ = logging::Log("main");
};

inline void swap(Sound& a, Sound& b) noexcept { a.swap(b); }

}  // namespace sound
} /* namespace game_engine */

#endif /* SRC_SOUND_SOUND_HPP_ */
