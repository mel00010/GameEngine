/******************************************************************************
 * main.cpp
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

#include <iostream>
#include <string>
#include <string_view>
#include <utility>

#include <boost/predef.h>

#include "third_party/libc++/compare.h"
#include "third_party/libstdc++/source_location.h"

#include "Util/str_const.hpp"

template <typename... Args>
void printer(std::string function_name, std::string file_name,
             std::uint_least32_t line, std::uint_least32_t column,
             Args... args) {
  std::cout << file_name << "(" << line << ":" << column
            << "): " << function_name << ":    ";
  using expander = int[];
  (void)expander{0, (void(std::cout << std::forward<Args>(args) << ','), 0)...};
  std::cout << std::endl;
}

template <typename... Args>
void printer(const std::source_location& loc, Args... args) {
  printer(loc.function_name(), loc.file_name(), loc.line(), loc.column(),
          args...);
}

class Log {
 private:
  using sl = std::source_location;

 public:
  Log() {}

#if BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(9, 0, 0) || \
    defined(__IN_ECLIPSE_PARSER__)
  template <typename... Args, typename SL = std::source_location>
  void Trace(Args... all, SL sl = SL::current()) {
    printer(sl.function_name(), sl.file_name(), sl.line(), sl.column(), all...);
  }
  template <typename... Args, typename File_name = const char*,
            typename Function_name = const char*,
            typename Line = std::uint_least32_t,
            typename Column = std::uint_least32_t>
  void Debug(Args... all, File_name file_name = sl::current().file_name(),
             Function_name function_name = sl::current().function_name(),
             Line line = sl::current().line(),
             Column column = sl::current().column()) {
    printer(function_name, file_name, line, column, all...);
  }
  template <typename... Args, typename File_name = const char*,
            typename Function_name = const char*,
            typename Line = std::uint_least32_t,
            typename Column = std::uint_least32_t>
  void Info(Args... all, File_name file_name = sl::current().file_name(),
            Function_name function_name = sl::current().function_name(),
            Line line = sl::current().line(),
            Column column = sl::current().column()) {
    printer(function_name, file_name, line, column, all...);
  }

  template <typename... Args, typename File_name = const char*,
            typename Function_name = const char*,
            typename Line = std::uint_least32_t,
            typename Column = std::uint_least32_t>
  void Warn(Args... all, File_name file_name = sl::current().file_name(),
            Function_name function_name = sl::current().function_name(),
            Line line = sl::current().line(),
            Column column = sl::current().column()) {
    printer(function_name, file_name, line, column, all...);
  }

  template <typename... Args, typename File_name = const char*,
            typename Function_name = const char*,
            typename Line = std::uint_least32_t,
            typename Column = std::uint_least32_t>
  void Error(Args... all, File_name file_name = sl::current().file_name(),
             Function_name function_name = sl::current().function_name(),
             Line line = sl::current().line(),
             Column column = sl::current().column()) {
    printer(function_name, file_name, line, column, all...);
  }
  template <typename... Args, typename File_name = const char*,
            typename Function_name = const char*,
            typename Line = std::uint_least32_t,
            typename Column = std::uint_least32_t>
  void Crit(Args... all, File_name file_name = sl::current().file_name(),
            Function_name function_name = sl::current().function_name(),
            Line line = sl::current().line(),
            Column column = sl::current().column()) {
    printer(function_name, file_name, line, column, all...);
  }
#else  /* __cpp_nontype_template_args == true*/
//  template <typename... Args, std::uint_least32_t line = sl::current().line(),
//            std::uint_least32_t column = sl::current().column()>
//  void Trace(
//      Args... all,
//      ::Log::LogString file_name = LogString(sl::current().file_name()),
//      ::Log::LogString function_name = LogString(sl::current().file_name())) {
//    printer(function_name.string, file_name.string, line, column, all...);
//  }
//  template <typename... Args,
//            str_const file_name = str_const(sl::current().file_name()),
//            str_const function_name = str_const(sl::current().file_name()),
//            std::uint_least32_t line = sl::current().line(),
//            std::uint_least32_t column = sl::current().column()>
//  void Debug(Args... all) {
//    printer(function_name, file_name, line, column, all...);
//  }
//  template <typename... Args,
//            str_const file_name = str_const(sl::current().file_name()),
//            str_const function_name =
//            str_const(sl::current().function_name()), std::uint_least32_t line
//            = sl::current().line(), std::uint_least32_t column =
//            sl::current().column()>
//  void Info(Args... all) {
//    printer(function_name, file_name, line, column, all...);
//  }
//
//  template <typename... Args,
//            str_const file_name = str_const(sl::current().file_name()),
//            str_const function_name =
//            str_const(sl::current().function_name()), std::uint_least32_t line
//            = sl::current().line(), std::uint_least32_t column =
//            sl::current().column()>
//  void Warn(Args... all) {
//    printer(function_name, file_name, line, column, all...);
//  }
//
//  template <typename... Args,
//            str_const file_name = str_const(sl::current().file_name()),
//            str_const function_name =
//            str_const(sl::current().function_name()), std::uint_least32_t line
//            = sl::current().line(), std::uint_least32_t column =
//            sl::current().column()>
//  void Error(Args... all) {
//    printer(function_name, file_name, line, column, all...);
//  }
//  template <typename... Args,
//            str_const file_name = str_const(sl::current().file_name()),
//            str_const function_name =
//            str_const(sl::current().function_name()), std::uint_least32_t line
//            = sl::current().line(), std::uint_least32_t column =
//            sl::current().column()>
//  void Crit(Args... all) {
//    printer(function_name, file_name, line, column, all...);
//  }
#endif /* BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(9, 0, 0) */
};

int main(int argc, char* argv[]) {
  int arg1 = 1;
  int arg2 = 2;

  Log log;

#if BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(9, 0, 0)
  log.Trace<int, int>(arg1, arg2);
  log.Trace(arg1, arg2);
  log.Debug(arg1, arg2);
  log.Info(arg1, arg2);
  log.Warn(arg1, arg2);
  log.Error(arg1, arg2);
  log.Crit(arg1, arg2);
  log.Debug(arg1, arg2);
#endif /* BOOST_COMP_GCC >= BOOST_VERSION_NUMBER(9, 0, 0) */

  return 0;
}
