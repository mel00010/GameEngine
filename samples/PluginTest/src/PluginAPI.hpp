/******************************************************************************
 * PluginAPI.hpp
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
#ifndef SAMPLES_PLUGINTEST_SRC_PLUGINAPI_HPP_
#define SAMPLES_PLUGINTEST_SRC_PLUGINAPI_HPP_

#include <string>

#include <boost/config.hpp>

namespace plugin {
class BOOST_SYMBOL_VISIBLE PluginAPI {
 public:
  virtual std::string name() const;
  virtual float calculate(float x, float y);
  virtual int calculate(int x, int y);
  static std::size_t size() { return sizeof(PluginAPI); }
  PluginAPI(const std::string& name) {}
  PluginAPI() {}
  virtual ~PluginAPI(){};
  static int value;
};

}  // namespace plugin
#endif /* SAMPLES_PLUGINTEST_SRC_PLUGINAPI_HPP_ */
