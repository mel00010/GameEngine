/******************************************************************************
 * Telemetry.hpp
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
#ifndef SRC_LOGGING_TELEMETRY_HPP_
#define SRC_LOGGING_TELEMETRY_HPP_

#include <cstdarg>
#include <cstddef>
#include <string>

#include "P7_Telemetry.h"

namespace game_engine {
namespace logging {

class Telemetry {
 public:
  Telemetry() noexcept = default;
  Telemetry &operator=(const Telemetry &rhs) = default;
  Telemetry(const Telemetry &rhs) = default;
  Telemetry &operator=(Telemetry &&rhs) noexcept = default;
  Telemetry(Telemetry &&rhs) noexcept = default;

  explicit Telemetry(const std::string name) noexcept;
  ~Telemetry() noexcept;

 private:
  IP7_Telemetry *telemetry_ = nullptr;
};

} /* namespace logging */
} /* namespace game_engine */

#endif /* SRC_LOGGING_TELEMETRY_HPP_ */
