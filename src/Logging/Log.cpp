/******************************************************************************
 * Log.cpp
 * Copyright (C) 2020  Mel McCalla <melmccalla@gmail.com>
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

#include "Log.hpp"

#include "Client.hpp"

namespace game_engine {
namespace logging {

Log::Log(const std::string name) noexcept {
  if ((trace_ = P7_Get_Shared_Trace(name.c_str())) == nullptr) {
  }
}

Log::~Log() noexcept { trace_->Release(); }

} /* namespace logging */
} /* namespace game_engine */
