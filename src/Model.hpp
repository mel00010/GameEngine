/******************************************************************************
 * Model.hpp
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
#ifndef SRC_MODEL_HPP_
#define SRC_MODEL_HPP_

#define GLM_ENABLE_EXPERIMENTAL

#include "GL.hpp"
#include "Mesh.hpp"
#include "Primitive.hpp"
#include "Program.hpp"
#include "Texture.hpp"
#include "Vertex.hpp"

#include <GL/glew.h>
#include <glm/gtx/euler_angles.hpp>

#include <vector>


namespace GameEngine {

class Model {
	public:
		Model() {};
		Model(Mesh _mesh) : mesh(_mesh) {}

		void init(Mesh _mesh) { mesh = _mesh; }
	public:
		void rotate(glm::vec3 delta);
		void move(glm::vec3 delta);
		void scale(double scale);

		void draw(ProgramRef prog);

	public:
		glm::mat4 model = glm::mat4(1.0f);
	protected:
		Mesh mesh;
};

} /* namespace GameEngine */

#endif /* SRC_MODEL_HPP_ */
