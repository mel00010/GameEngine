/******************************************************************************
 * Client.cpp
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

#include "Client.hpp"

#include <gflags/gflags.h>

#include <iostream>
#include <ostream>
#include <string>

inline constexpr size_t kMaxNameLength = 96;
inline constexpr int kPortMax = 65535;
inline constexpr int kPacketSizeMin = 512;
inline constexpr int kPacketSizeMax = 65535;
inline constexpr std::string_view kLogFormatDefaultString(
    "\"{%cn} [%tf] %lv %ms\"");

namespace {
namespace validators {

bool ValidateP7Sink(const char* flagname, const std::string& value) {
  if (value == "baical") {
    return true;
  }
  if (value == "binary") {
    return true;
  }
  if (value == "text") {
    return true;
  }
  if (value == "console") {
    return true;
  }
  if (value == "syslog") {
    return true;
  }
  if (value == "auto") {
    return true;
  }
  if (value == "null") {
    return true;
  }
  std::cerr << "Invalid value for " << flagname << ":  " << value
            << ".  "
               "Must be one of \"baical\", \"binary\", \"text\", \"console\","
               "\"syslog\", \"auto\" or \"null\".  "
            << std::endl;
  return false;
}

bool ValidateLogName(const char* flagname, const std::string& value) {
  if (value.length() > kMaxNameLength) {
    std::cerr << "Invalid value for " << flagname << ":  " << value
              << ".  Value is too long (" << value.length() << " characters).  "
              << "Length must be less than or equal to " << kMaxNameLength
              << ". " << std::endl;
    return false;
  }
  return true;
}

bool ValidateLogAddress(const char* flagname, const std::string& value) {
  if (FLAGS_log_sink != "baical" && FLAGS_log_sink != "auto") {
    std::cerr
        << "Flag " << flagname << " may not be used with log_sink "
        << FLAGS_log_sink
        << ".  Flag may only be used with log_sink=biacal or log_sink=auto."
        << std::endl;
    return false;
  }
  return true;
}

bool ValidateLogPort(const char* flagname, const std::int32_t value) {
  if (FLAGS_log_sink != "baical" && FLAGS_log_sink != "auto") {
    std::cerr
        << "Flag " << flagname << " may not be used with log_sink "
        << FLAGS_log_sink
        << ".  Flag may only be used with log_sink=biacal or log_sink=auto."
        << std::endl;
    return false;
  }

  if (value > 0 && value <= kPortMax) {
    return true;
  }

  std::cerr << "Invalid value for " << flagname << ":  " << value
            << ".  Value must be between 0 and " << kPortMax << ".  "
            << std::endl;
  return false;
}

bool ValidateLogPacketSize(const char* flagname, const std::int32_t value) {
  if (FLAGS_log_sink != "baical" && FLAGS_log_sink != "auto") {
    std::cerr
        << "Flag " << flagname << " may not be used with log_sink "
        << FLAGS_log_sink
        << ".  Flag may only be used with log_sink=biacal or log_sink=auto."
        << std::endl;
    return false;
  }
  if (value >= kPacketSizeMin && value <= kPacketSizeMax) {
    return true;
  }

  std::cerr << "Invalid value for " << flagname << ":  " << value
            << ".  Value must be between " << kPacketSizeMin << " and "
            << kPacketSizeMax << ".  " << std::endl;
  return false;
}

bool ValidateLogWindow(const char* flagname, const std::int32_t value) {}

bool ValidateLogEto(const char* flagname, const std::int32_t value) {}

bool ValidateLogFormat(const char* flagname, const std::string& value) {
  if (FLAGS_log_sink != "text" && FLAGS_log_sink != "console" &&
      FLAGS_log_sink != "syslog") {
    if (value == std::string(kLogFormatDefaultString)) {
      FLAGS_log_format = "";
      return true;
    }
    std::cerr << "Flag " << flagname << " may not be used with log_sink "
              << FLAGS_log_sink << ".  "
              << "Flag may only be used with log_sink=text, log_sink=console, "
              << "or log_sink=syslog." << std::endl;
    return false;
  }
  return true;
}

bool ValidateLogFacility(const char* flagname, const std::int32_t value) {}

} /* namespace validators */
} /* namespace */

DEFINE_string(log_sink, "baical",
              "Sink to use for P7 logging client.  "
              "Must be one of \"baical\", \"binary\", \"text\", \"console\","
              "\"syslog\", \"auto\" or \"null\".  ");
DEFINE_validator(log_sink, &::validators::ValidateP7Sink);

DEFINE_string(log_name, "", "Name to use for p7 client instance.");
DEFINE_validator(log_name, &::validators::ValidateLogName);

DEFINE_bool(logging, true, "Enable/disable logging with p7.");
DEFINE_int32(log_pool_size, 4096, "Size of memory pool to use for logging.");

DEFINE_string(log_address, "127.0.0.1",
              "What address to log to if using baical or auto sinks.");
DEFINE_validator(log_address, &::validators::ValidateLogAddress);

DEFINE_int32(log_port, 9010,
             "What port for log server to listen on.  "
             "Only allowed if log_sink=biacal or log_sink=auto.");
DEFINE_validator(log_port, &::validators::ValidateLogPort);

DEFINE_int32(log_packet_size, 512,
             "Size of log packets in bytes."
             "Only allowed if log_sink=biacal or log_sink=auto.");
DEFINE_validator(log_packet_size, &::validators::ValidateLogPacketSize);

DEFINE_int32(log_window, 0,
             "Size of log transmission window in packets, used to"
             " optimize transmission speed.  Advanced.  "
             "Only allowed if log_sink=biacal or log_sink=auto.");
DEFINE_validator(log_window, &::validators::ValidateLogWindow);

DEFINE_int32(log_eto, 0,
             "Transmission timeout in seconds before P7 log object "
             "has to be closed.  "
             "Only allowed if log_sink=biacal or log_sink=auto.");
DEFINE_validator(log_eto, &::validators::ValidateLogEto);

DEFINE_string(
    log_format, std::string(kLogFormatDefaultString).c_str(),
    "Log item format string for text sinks (log_sink=text, log_sink=console, "
    "or log_sink=syslog).");
DEFINE_validator(log_format, &::validators::ValidateLogFormat);

DEFINE_int32(log_facility, 1,
             "Syslog facility to use for syslog logging sink "
             "(log_sink=syslog).");
DEFINE_validator(log_facility, &::validators::ValidateLogFacility);

namespace game_engine {
namespace logging {

Client::Client(const std::string name) noexcept {
  if ((client_ = P7_Get_Shared(name.c_str())) == nullptr) {
    std::cerr << FLAGS_log_sink;
  }
}

Client::~Client() {
  //	client_->Release();
}

} /* namespace logging */
} /* namespace game_engine */
