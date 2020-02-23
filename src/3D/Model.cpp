/******************************************************************************
 * Model.cpp
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

#include "Model.hpp"
#include "Vertex.hpp"

#include <Log.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace game_engine {
namespace _3D {

std::vector<Texture> Model::textures_loaded_;

std::ostream& operator<<(std::ostream& os, Model m) {
	os << "Model {" << std::endl << push_indent;

	os << "glm::mat4 model_ = " << push_indent << m.model_ << pop_indent << std::endl;

	os << "std::vector<Texture> textures_loaded_ = { " << std::endl;
	os << push_indent;
	for (auto& i : m.textures_loaded_) {
		os << i << ", " << std::endl;
	}
	os << pop_indent;
	os << "}" << std::endl;

	os << "std::vector<Mesh> meshes_ = {" << std::endl;
	os << push_indent;
	for (auto& i : m.meshes_) {
		os << i << ", " << std::endl;
	}
	os << pop_indent;
	os << "}" << std::endl;
	os << "cmrc::embedded_filesystem* fs_ = " << m.fs_ << std::endl;
	os << "std::string directory_ = \"" << m.directory_ << "\"" << std::endl;
	os << "std::string folder_ = \"" << m.folder_ << "\"" << std::endl;
	os << "bool gamma_correction_ = " << m.gamma_correction_ << std::endl;

	os << pop_indent << "}";
	return os;
}

} /* namespace _3D */
} /* namespace game_engine */
