/******************************************************************************
 * GLWindowManager.cpp
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

#include "GL/GLWindowManager.hpp"

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "LoggerV2/Log.hpp"

namespace game_engine {
namespace gl {

SDL_Window* GLWindowManager::window_ = nullptr;

void GLWindowManager::Init(std::string program_name) {
  //	setWindow(SDL_CreateWindow(program_name.c_str(),
  //		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
  //		1920, 1080,
  //		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL));
  //	SDL_GL_CreateContext(getWindow());
  //	enableVSync();
}

SDL_Window* GLWindowManager::GetWindow() { return window_; }
void GLWindowManager::SetWindow(SDL_Window* p) { window_ = p; }

glm::ivec2 GLWindowManager::GetWindowSize() {
  glm::ivec2 v(0, 0);
  SDL_GetWindowSize(window_, &v.x, &v.y);
  return v;
}

void GLWindowManager::SetFullscreen(bool enable) {
  if (SDL_GetDesktopDisplayMode(SDL_GetWindowDisplayIndex(window_), &native_) !=
      0) {
    // In case of error...
    log_.Error("Could not get display mode for video display #{}: {}",
               SDL_GetWindowDisplayIndex(window_), SDL_GetError());
    throw EXIT_FAILURE;
  } else {
    // On success, print the current display mode.
    log_.Debug("Display #{}: native display mode is {}x{}px @ {}hz.",
               SDL_GetWindowDisplayIndex(window_), native_.w, native_.h,
               native_.refresh_rate);
  }
  is_screen_fullscreen_ = enable;
  if (is_screen_fullscreen_) {
    current_ = native_;
    SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN);
    SDL_SetWindowDisplayMode(window_, &current_);
  } else {
    current_ = native_;
    SDL_SetWindowFullscreen(window_, 0);
  }
}
bool GLWindowManager::IsFullscreen() { return is_screen_fullscreen_; }
void GLWindowManager::ToggleFullscreen() {
  SetFullscreen(!is_screen_fullscreen_);
}

void GLWindowManager::SetVSyncEnabled(bool enable) {
  vsync_enabled_ = enable;
  SDL_GL_SetSwapInterval(vsync_enabled_);
}
bool GLWindowManager::IsVSyncEnabled() { return vsync_enabled_; }
void GLWindowManager::EnableVSync() { SetVSyncEnabled(true); }
void GLWindowManager::DisableVSync() { SetVSyncEnabled(false); }
void GLWindowManager::ToggleVSync() { SetVSyncEnabled(!vsync_enabled_); }

void GLWindowManager::Quit() {
  SDL_Event sdlevent;
  sdlevent.type = SDL_QUIT;
  SDL_PushEvent(&sdlevent);
}

bool GLWindowManager::IsCursorDisabled() { return cursor_disabled_; }
void GLWindowManager::DisableCursor(bool disabled) {
  cursor_disabled_ = disabled;
  if (cursor_disabled_) {
    SDL_ShowCursor(SDL_DISABLE);
    SDL_SetRelativeMouseMode(SDL_TRUE);
  } else {
    SDL_ShowCursor(SDL_ENABLE);
    SDL_SetRelativeMouseMode(SDL_FALSE);
  }
}
bool GLWindowManager::ToggleCursor() {
  if (cursor_disabled_) {
    cursor_disabled_ = false;
    SDL_ShowCursor(SDL_ENABLE);
    SDL_SetRelativeMouseMode(SDL_FALSE);
  } else {
    cursor_disabled_ = true;
    SDL_ShowCursor(SDL_DISABLE);
    SDL_SetRelativeMouseMode(SDL_TRUE);
  }
  return cursor_disabled_;
}

void GLWindowManager::RedrawWindowBounds(glm::ivec2 size) {
  glViewport(0, 0, size.x, size.y);
}

} /* namespace gl */
} /* namespace game_engine */
