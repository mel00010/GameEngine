/******************************************************************************
 * Program.hpp
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
#ifndef SRC_PROGRAM_HPP_
#define SRC_PROGRAM_HPP_


#include <GL/glew.h>
#include <glm/glm.hpp>

#include <memory>
#include <vector>


namespace GameEngine {
namespace GL {

class Attribute;
class Shader;

using AttributeRef = std::shared_ptr<Attribute>;
using ShaderRef = std::shared_ptr<Shader>;


class Program {
	public:
		Program();
		~Program();
	public:
		void attachShader(ShaderRef shader);
		void addAttribute(AttributeRef attribute);

		bool link();
		bool init();
	public:
		bool isValid() const;
		void setValid(bool validity = false);

		GLuint getProgramHandle();
		GLuint getPH();
		std::vector<AttributeRef>& getAttributes();

		void useProgram();
		void use();

		void setBool(const std::string &name, bool value) const;
		void setInt(const std::string &name, int value) const;
		void setFloat(const std::string &name, float value) const;
		void setVec2(const std::string &name, const glm::vec2 &value) const;
		void setVec2(const std::string &name, float x, float y) const;
		void setVec3(const std::string &name, const glm::vec3 &value) const;
		void setVec3(const std::string &name, float x, float y, float z) const;
		void setVec4(const std::string &name, const glm::vec4 &value) const;
		void setVec4(const std::string &name, float x, float y, float z, float w) const;
		void setMat2(const std::string &name, const glm::mat2 &mat) const;
		void setMat3(const std::string &name, const glm::mat3 &mat) const;
		void setMat4(const std::string &name, const glm::mat4 &mat) const;
	private:
		GLuint program;
		bool valid;

		std::vector<ShaderRef> shaders;
		std::vector<AttributeRef> attributes;
};

using ProgramRef = std::shared_ptr<Program>;

} /* namespace GL */
} /* namespace GameEngine */

#endif /* SRC_PROGRAM_HPP_ */
