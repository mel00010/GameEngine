/******************************************************************************
 * Shader.hpp
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
#ifndef SRC_SHADER_HPP_
#define SRC_SHADER_HPP_

#include <Util/ResourceDefs.hpp>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>

#include <memory>
#include <ostream>
#include <string>

namespace GameEngine {
namespace GL {

enum class ShaderType : GLenum {
		VERTEX = GL_VERTEX_SHADER,
		TESS_CONTROL = GL_TESS_CONTROL_SHADER,
		TESS_EVALUATION = GL_TESS_EVALUATION_SHADER,
		GEOMETRY = GL_GEOMETRY_SHADER,
		FRAGMENT = GL_FRAGMENT_SHADER,
		COMPUTE = GL_COMPUTE_SHADER
};
inline std::ostream& operator<<(std::ostream& os, ShaderType type) {
	switch(type) {
		case ShaderType::VERTEX: 			return os << "ShaderType::VERTEX";
		case ShaderType::TESS_CONTROL:		return os << "ShaderType::TESS_CONTROL";
		case ShaderType::TESS_EVALUATION:	return os << "ShaderType::TESS_EVALUATION";
		case ShaderType::GEOMETRY:			return os << "ShaderType::GEOMETRY";
		case ShaderType::FRAGMENT:			return os << "ShaderType::FRAGMENT";
		case ShaderType::COMPUTE:			return os << "ShaderType::COMPUTE";
	}
	return os;
}

class Shader {
	public:
		template<Enum ResourceID> Shader(Resource<ResourceID> resource, ShaderType _type) :
				type(_type), shader(glCreateShader(static_cast<GLenum>(_type))),
				valid(false) {
			std::string file_location;
			char* base_path = SDL_GetBasePath();
			if (base_path) {
				file_location = base_path;
			} else {
				file_location = SDL_strdup("./");
			}

			file_location+=resource.file_path;
			std::ifstream file(file_location);
			source = std::string((std::istreambuf_iterator<char>(file)),
					 std::istreambuf_iterator<char>());
		}
		Shader(std::string source, ShaderType type);
		~Shader();
		bool init();

	public:
		bool isValid() const;
		ShaderType getShaderType();
		GLuint getShaderHandle();
	private:
		std::string source;
		ShaderType type;
		GLuint shader;
		bool valid;
};

using ShaderRef = std::shared_ptr<Shader>;

} /* namespace GL */
} /* namespace GameEngine */


#endif /* SRC_SHADER_HPP_ */
