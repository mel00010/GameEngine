/******************************************************************************
 * Log.hpp
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
#ifndef SRC_LOGGING_LOG_HPP_
#define SRC_LOGGING_LOG_HPP_

#include <cstdarg>
#include <cstddef>
#include <string>

#include "P7_Trace.h"

namespace game_engine {
namespace logging {

class Log {
 public:
  Log() noexcept = default;
  Log &operator=(const Log &rhs) = default;
  Log(const Log &rhs) = default;
  Log &operator=(Log &&rhs) noexcept = default;
  Log(Log &&rhs) noexcept = default;

  explicit Log(const std::string name) noexcept;
  ~Log() noexcept;

  void swap(Log &other) noexcept {
    using std::swap;
    swap(other.trace_, trace_);
  }

 private:
  IP7_Trace *trace_ = nullptr;
};

inline void swap(Log &a, Log &b) noexcept { a.swap(b); }

} /* namespace logging */
} /* namespace game_engine */

#endif /* SRC_LOGGING_LOG_HPP_ */
