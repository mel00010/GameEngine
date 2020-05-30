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

#include <string>
#include <utility>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <cmrc/cmrc.hpp>

#include "LoggerV2/Log.hpp"

namespace game_engine {
namespace sound {

class Music {
 public:
  Music() = default;
  Music& operator=(const Music& rhs) = default;
  Music(const Music& rhs) = default;
  Music& operator=(Music&& rhs) noexcept = default;
  Music(Music&& rhs) noexcept = default;

  explicit Music(const cmrc::file file) { LoadMusic(file); }
  ~Music() noexcept;

  Mix_Music* LoadMusic(const cmrc::file file);

 public:
  void Play(const size_t times = 1);
  void Pause();
  void Resume();
  void Halt();
  int SetVolume(const int volume);
  bool IsPaused();
  bool IsPlaying();

 public:
  std::string path_ = "";
  Mix_Music* music_ = nullptr;

  void swap(Music& other) noexcept {
    using std::swap;
    swap(other.path_, path_);
    swap(other.music_, music_);
  }

 private:
  logging::Log log_ = logging::Log("main");
};

inline void swap(Music& a, Music& b) noexcept { a.swap(b); }

}  // namespace sound
} /* namespace game_engine */

#endif /* SRC_SOUND_MUSIC_HPP_ */
