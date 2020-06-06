/******************************************************************************
 * WindowManager.hpp
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
#ifndef SRC_WINDOWMANAGER_HPP_
#define SRC_WINDOWMANAGER_HPP_

#include <string>

#include <glm/glm.hpp>

#include "Util/Crtp.hpp"

namespace game_engine {

template <typename Derived>
class WindowManager : Crtp<WindowManager, Derived> {
 public:
  void Init(std::string program_name) { this->Underlying().Init(program_name); }
  static glm::ivec2 GetWindowSize() { return Derived::GetWindowSize(); }

  void SetFullscreen(bool enable = false) {
    this->Underlying().SetFullscreen(enable);
  }
  bool IsFullscreen() { return this->Underlying().IsFullscreen(); }
  void ToggleFullscreen() { this->Underlying().ToggleFullscreen(); }

  void SetVSyncEnabled(bool enable = false) {
    this->Underlying().SetVSyncEnabled(enable);
  }
  bool IsVSyncEnabled() { return this->Underlying().IsVSyncEnabled(); }
  void EnableVSync() { this->Underlying().EnableVSync(); }
  void DisableVSync() { this->Underlying().DisableVSync(); }
  void ToggleVSync() { this->Underlying().ToggleVSync(); }

  void Quit() { this->Underlying().Quit(); }
  bool IsCursorDisabled() { return this->Underlying().IsCursorDisabled(); }
  void DisableCursor(bool disabled = true) {
    this->Underlying().DisableCursor(disabled);
  }
  bool RoggleCursor() { return this->Underlying().ToggleCursor(); }

  void RedrawWindowBounds(glm::ivec2 size) {
    this->Underlying().RedrawWindowBounds(size);
  }
};

} /* namespace game_engine */

#endif /* SRC_WINDOWMANAGER_HPP_ */
