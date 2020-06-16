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
#include <memory>
#include <string>

#include <boost/dll/alias.hpp>
#include <boost/dll/import_mangled.hpp>
#include <boost/dll/smart_library.hpp>
#include <boost/filesystem.hpp>

#include "PluginAPI.hpp"
#include "import_class.hpp"
class alias {};
void not_smart(char** argv);

int main(int argc, char* argv[]) {
  //  not_smart(argv);
  //  return 0;
  // argv[1] contains path to directory with our plugin library
  boost::filesystem::path lib_path(argv[1]);
  // smart library instance
  boost::dll::experimental::smart_library lib(
      lib_path, boost::dll::load_mode::rtld_global);

  // get the size function
  auto size_f = boost::dll::experimental::import_mangled<std::size_t()>(
      lib, "plugin::MyPlugin::size");
  std::cout << "Loaded size" << std::endl;
  std::size_t size = size_f();  // get the size of the class
  std::cout << "Called size" << std::endl;
  std::cout << "size = " << size << std::endl;
  auto value = boost::dll::experimental::import_mangled<int>(
      lib, "plugin::MyPlugin::value");
  std::cout << "Loaded value" << std::endl;
  std::cout << "value = " << *value << std::endl;
  std::string name_ = "MyName";
  auto cl = boost::dll::experimental::import_class<class alias, std::string>(
      lib, "plugin::MyPlugin", size, name_);
  std::cout << "Loaded class" << std::endl;
  auto name =
      boost::dll::experimental::import_mangled<class alias, const char*(int)>(
          lib, "name");
  std::cout << "Name: " << (cl->*name)(1) << std::endl;
  auto calc =
      boost::dll::experimental::import_mangled<class alias, float(float, float),
                                               int(int, int)>(lib, "calculate");
  std::cout << "Calc(float): " << (cl->*calc)(5.f, 2.f) << std::endl;
  std::cout << "Calc(int):   " << (cl->*calc)(5, 2) << std::endl;
  const std::type_info& ti = cl.get_type_info();
}

void not_smart(char** argv) {
  boost::filesystem::path lib_path(argv[1]);
  // smart library instance
  boost::dll::experimental::smart_library lib(lib_path);

  // get the size function
  auto size_f = lib.get_function<std::size_t()>("plugin::MyPlugin::size");

  std::size_t size = size_f();  // get the size of the class

  // allocate a buffer for the import
  std::unique_ptr<char[]> buffer(new char[size]);

  // cast it to our alias type.
  alias& inst = *reinterpret_cast<alias*>(buffer.get());

  // add an alias, so i can import a class that is not declared here
  lib.add_type_alias<class alias>("plugin::MyPlugin");

  // get the constructor
  auto ctor = lib.get_constructor<alias(const std::string&)>();

  // call the non-allocating constructor. The allocating-constructor is a
  // non-portable feature
  ctor.call_standard(&inst, "MyName");

  // import the name function
  auto name_f = lib.get_mem_fn<const alias, std::string()>("name");
  std::cout << "Name Call: " << (inst.*name_f)() << std::endl;

  // import both calculate functions
  auto calc_f = lib.get_mem_fn<alias, float(float, float)>("calculate");
  auto calc_i = lib.get_mem_fn<alias, int(int, int)>("calculate");

  std::cout << "calc(float): " << (inst.*calc_f)(5., 2.) << std::endl;
  std::cout << "calc(int)  : " << (inst.*calc_f)(5, 2) << std::endl;

  auto& var = lib.get_variable<int>("plugin::MyPlugin::value");
  std::cout << "value " << var << std::endl;

  auto dtor = lib.get_destructor<alias>();  // get the destructor
  dtor.call_standard(&inst);
}
