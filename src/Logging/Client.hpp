/******************************************************************************
 * Client.hpp
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
#ifndef SRC_LOGGING_CLIENT_HPP_
#define SRC_LOGGING_CLIENT_HPP_

#include <P7_Client.h>
#include <gflags/gflags.h>

#include <cstdarg>
#include <cstddef>
#include <string>

DECLARE_string(log_sink);
DECLARE_string(log_name);
DECLARE_bool(logging);
DECLARE_int32(log_pool_size);
DECLARE_string(log_address);
DECLARE_int32(log_port);
DECLARE_int32(log_packet_size);
DECLARE_int32(log_window);
DECLARE_int32(log_eto);
DECLARE_string(log_format);
DECLARE_int32(log_facility);

namespace game_engine {
namespace logging {

class Client {
 public:
  Client() noexcept = default;
  Client &operator=(const Client &rhs) = default;
  Client(const Client &rhs) = default;
  Client &operator=(Client &&rhs) noexcept = default;
  Client(Client &&rhs) noexcept = default;

  explicit Client(const std::string name) noexcept;
  ~Client() noexcept;

 private:
  IP7_Client *client_ = nullptr;
};

} /* namespace logging */
} /* namespace game_engine */

#endif /* SRC_LOGGING_CLIENT_HPP_ */
