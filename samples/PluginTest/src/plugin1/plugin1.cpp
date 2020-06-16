/******************************************************************************
 * plugin1.cpp
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

#include "../PluginAPI.hpp"
namespace plugin {

class BOOST_SYMBOL_EXPORT MyPlugin {
 public:
  BOOST_SYMBOL_EXPORT std::string name(int a) const;
  BOOST_SYMBOL_EXPORT float calculate(float x, float y);
  BOOST_SYMBOL_EXPORT int calculate(int x, int y);
  BOOST_SYMBOL_EXPORT static std::size_t size();
  BOOST_SYMBOL_EXPORT MyPlugin(std::string name);
  BOOST_SYMBOL_EXPORT MyPlugin(std::string name);
  BOOST_SYMBOL_EXPORT MyPlugin();
  BOOST_SYMBOL_EXPORT virtual ~MyPlugin();
  BOOST_SYMBOL_EXPORT static int value;

 private:
  std::string _name;
};

int MyPlugin::value = 0;
std::string MyPlugin::name(int a) const { return "test"; }
float MyPlugin::calculate(float x, float y) {
  std::cout << "float x = " << x << ", float y =" << y << std::endl;
  return x * y;
}
int MyPlugin::calculate(int x, int y) {
  std::cout << "int x = " << x << ", int y =" << y << std::endl;
  return x * y;
}
std::size_t MyPlugin::size() { return sizeof(MyPlugin); }
MyPlugin::MyPlugin(std::string name) {
  std::cout << "Name = " << _name << std::endl;
  _name = name;
}
MyPlugin::MyPlugin() {}
MyPlugin::~MyPlugin() {}

}  // namespace plugin
