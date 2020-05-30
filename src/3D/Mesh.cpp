/******************************************************************************
 * Mesh.cpp
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

#include "3D/Mesh.hpp"

#include "LoggerV2/Log.hpp"

namespace game_engine {
namespace _3D {

Mesh::Mesh(const std::vector<Vertex>& vertices,
           const std::vector<GLuint>& indices,
           const std::vector<Texture>& textures, const Primitive mode)
    : vertices_(vertices), indices_(indices), textures_(textures), mode_(mode) {
  GLuint diffuse_num = 0;
  GLuint specular_num = 0;
  GLuint normal_num = 0;
  GLuint height_num = 0;

  for (GLuint i = 0; i < textures.size(); i++) {
    switch (textures[i].type_) {
      case TextureType::DIFFUSE:
        texture_strings_.push_back("texture_diffuse" +
                                   std::to_string(diffuse_num++));
        break;
      case TextureType::SPECULAR:
        texture_strings_.push_back("texture_specular" +
                                   std::to_string(specular_num++));
        break;
      case TextureType::NORMAL:
        texture_strings_.push_back("texture_normal" +
                                   std::to_string(normal_num++));
        break;
      case TextureType::HEIGHT:
        texture_strings_.push_back("texture_normal" +
                                   std::to_string(height_num++));
        break;
    }
  }
}

std::ostream& operator<<(std::ostream& os, const Mesh& m) {
  os << "Mesh {" << std::endl;
  os << "std::vector<Vertex> vertices = [ " << std::endl;
  for (auto& i : m.vertices_) {
    os << i << ", " << std::endl;
  }
  os << "]" << std::endl;
  os << "std::vector<GLuint> indices = [ " << std::endl;
  for (auto& i : m.indices_) {
    os << i << ", " << std::endl;
  }
  os << "]" << std::endl;
  os << "std::vector<Texture> textures = [ " << std::endl;
  for (auto& i : m.textures_) {
    os << i << ", " << std::endl;
  }
  os << "]" << std::endl;
  os << "VBO_handle handle = " << m.handle_ << std::endl;
  os << "std::vector<std::string> texture_strings = [ " << std::endl;
  for (auto& i : m.texture_strings_) {
    os << "\"" << i << "\", " << std::endl;
  }
  os << "Primitive mode = " << m.mode_ << std::endl;
  os << "}";
  return os;
}

} /* namespace _3D */
} /* namespace game_engine */
