/******************************************************************************
 * GLWindowManager.hpp
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
#ifndef SRC_GL_GLWINDOWMANAGER_HPP_
#define SRC_GL_GLWINDOWMANAGER_HPP_

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include "WindowManager.hpp"

namespace game_engine {
namespace gl {

class GLWindowManager : public WindowManager<GLWindowManager> {
 public:
  void Init(std::string program_name);
  SDL_Window* GetWindow();
  void SetWindow(SDL_Window* p);

  static glm::ivec2 GetWindowSize();

  void SetFullscreen(bool enable = false);
  bool IsFullscreen();
  void ToggleFullscreen();

  void SetVSyncEnabled(bool enable = false);
  bool IsVSyncEnabled();
  void EnableVSync();
  void DisableVSync();
  void ToggleVSync();

  void Quit();
  bool IsCursorDisabled();
  void DisableCursor(bool disabled = true);
  bool ToggleCursor();

  void RedrawWindowBounds(glm::ivec2 size);

 public:
  static SDL_Window* window_;

 protected:
  bool cursor_disabled_ = false;
  bool is_screen_fullscreen_ = false;
  bool vsync_enabled_ = false;

  SDL_DisplayMode native_;
  SDL_DisplayMode current_;

 private:
  logging::Log log_ = logging::Log("main");
};

} /* namespace gl */
} /* namespace game_engine */

#endif /* SRC_GL_GLWINDOWMANAGER_HPP_ */
