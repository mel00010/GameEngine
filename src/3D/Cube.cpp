/******************************************************************************
 * Cube.cpp
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

#include "3D/Cube.hpp"

namespace game_engine {
namespace _3D {

std::ostream& operator<<(std::ostream& os, const Cube& m) {
  os << "Cube {" << std::endl;
  os << "Model model_ = " << m.model_ << std::endl;
  os << "}";
  return os;
}

std::ostream& operator<<(std::ostream& os, const Cube::CubeMesh& m) {
  os << "Cube::Mesh {" << std::endl;
  os << "std::vector<Vertex> vertices_ = [ " << std::endl;
  for (auto& i : m.vertices_) {
    os << i << ", " << std::endl;
  }
  os << "]" << std::endl;
  os << "std::vector<GLuint> indices_ = [ " << std::endl;
  for (auto& i : m.indices_) {
    os << i << ", " << std::endl;
  }
  os << "]" << std::endl;
  os << "VboHandle handle_ = " << m.handle_ << std::endl;
  os << "}";
  return os;
}

} /* namespace _3D */
} /* namespace game_engine */
