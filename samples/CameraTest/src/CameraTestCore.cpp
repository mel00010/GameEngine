/******************************************************************************
 * CameraTestCore.cpp
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

#include "CameraTestCore.hpp"

#include <Log.hpp>
#include <Model.hpp>
#include <Program.hpp>
#include <Resources.hpp>
#include <Shader.hpp>

#include <glm/glm.hpp>


using namespace GameEngine;

void CameraTestCore::setup() {
	p = std::make_shared<Program>();
	p->init();
	ShaderRef vertex_shader = std::make_shared<Shader>(Resources[static_cast<size_t>(ResourceID::VERTEX_SHADER)], ShaderType::VERTEX);
	ShaderRef fragment_shader = std::make_shared<Shader>(Resources[static_cast<size_t>(ResourceID::FRAGMENT_SHADER)], ShaderType::FRAGMENT);
	vertex_shader->init();
	fragment_shader->init();
	p->attachShader(vertex_shader);
	p->attachShader(fragment_shader);
	p->link();

	/* When all init functions run without errors,
	   the glsl_program can initialise the resources */
	if (!p->isValid()) {
		throw EXIT_FAILURE;
	}
	p->useProgram();

	gl.init();
	gl.bind();
	gl.allocate(sizeof(Vertex) * 36, sizeof(Vertex) * 36);
	// vertex
	gl.addVertexPointer(0, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, pos));
	gl.addVertexPointer(1, 2, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex));



	cube.init(Primitive::TRIANGLES, Texture().loadTexture(Resources[static_cast<size_t>(ResourceID::WALL)]));
	cube.addVertex(Vertex(glm::vec3(-0.5f, -0.5f, -0.5f),	glm::vec2(0.0f, 0.0f))); // 0
	cube.addVertex(Vertex(glm::vec3( 0.5f, -0.5f, -0.5f),	glm::vec2(1.0f, 0.0f))); // 1
	cube.addVertex(Vertex(glm::vec3( 0.5f,  0.5f, -0.5f),	glm::vec2(1.0f, 1.0f))); // 2
	cube.addVertex(Vertex(glm::vec3( 0.5f,  0.5f, -0.5f),	glm::vec2(1.0f, 1.0f))); // 3
	cube.addVertex(Vertex(glm::vec3(-0.5f,  0.5f, -0.5f),	glm::vec2(0.0f, 1.0f))); // 4
	cube.addVertex(Vertex(glm::vec3(-0.5f, -0.5f, -0.5f),	glm::vec2(0.0f, 0.0f))); // 5

	cube.addVertex(Vertex(glm::vec3(-0.5f, -0.5f,  0.5f),	glm::vec2(0.0f, 0.0f))); // 6
	cube.addVertex(Vertex(glm::vec3( 0.5f, -0.5f,  0.5f),	glm::vec2(1.0f, 0.0f))); // 7
	cube.addVertex(Vertex(glm::vec3( 0.5f,  0.5f,  0.5f),	glm::vec2(1.0f, 1.0f))); // 8
	cube.addVertex(Vertex(glm::vec3( 0.5f,  0.5f,  0.5f),	glm::vec2(1.0f, 1.0f))); // 9
	cube.addVertex(Vertex(glm::vec3(-0.5f,  0.5f,  0.5f),	glm::vec2(0.0f, 1.0f))); // 10
	cube.addVertex(Vertex(glm::vec3(-0.5f, -0.5f,  0.5f),	glm::vec2(0.0f, 0.0f))); // 11

	cube.addVertex(Vertex(glm::vec3(-0.5f,  0.5f,  0.5f),	glm::vec2(1.0f, 0.0f))); // 12
	cube.addVertex(Vertex(glm::vec3(-0.5f,  0.5f, -0.5f),	glm::vec2(1.0f, 1.0f))); // 13
	cube.addVertex(Vertex(glm::vec3(-0.5f, -0.5f, -0.5f),	glm::vec2(0.0f, 1.0f))); // 14
	cube.addVertex(Vertex(glm::vec3(-0.5f, -0.5f, -0.5f),	glm::vec2(0.0f, 1.0f))); // 15
	cube.addVertex(Vertex(glm::vec3(-0.5f, -0.5f,  0.5f),	glm::vec2(0.0f, 0.0f))); // 16
	cube.addVertex(Vertex(glm::vec3(-0.5f,  0.5f,  0.5f),	glm::vec2(1.0f, 0.0f))); // 17

	cube.addVertex(Vertex(glm::vec3( 0.5f,  0.5f,  0.5f),	glm::vec2(1.0f, 0.0f))); // 18
	cube.addVertex(Vertex(glm::vec3( 0.5f,  0.5f, -0.5f),	glm::vec2(1.0f, 1.0f))); // 19
	cube.addVertex(Vertex(glm::vec3( 0.5f, -0.5f, -0.5f),	glm::vec2(0.0f, 1.0f))); // 20
	cube.addVertex(Vertex(glm::vec3( 0.5f, -0.5f, -0.5f),	glm::vec2(0.0f, 1.0f))); // 21
	cube.addVertex(Vertex(glm::vec3( 0.5f, -0.5f,  0.5f),	glm::vec2(0.0f, 0.0f))); // 22
	cube.addVertex(Vertex(glm::vec3( 0.5f,  0.5f,  0.5f),	glm::vec2(1.0f, 0.0f))); // 23

	cube.addVertex(Vertex(glm::vec3(-0.5f, -0.5f, -0.5f),	glm::vec2(0.0f, 1.0f))); // 24
	cube.addVertex(Vertex(glm::vec3( 0.5f, -0.5f, -0.5f),	glm::vec2(1.0f, 1.0f))); // 25
	cube.addVertex(Vertex(glm::vec3( 0.5f, -0.5f,  0.5f),	glm::vec2(1.0f, 0.0f))); // 26
	cube.addVertex(Vertex(glm::vec3( 0.5f, -0.5f,  0.5f),	glm::vec2(1.0f, 0.0f))); // 27
	cube.addVertex(Vertex(glm::vec3(-0.5f, -0.5f,  0.5f),	glm::vec2(0.0f, 0.0f))); // 28
	cube.addVertex(Vertex(glm::vec3(-0.5f, -0.5f, -0.5f),	glm::vec2(0.0f, 1.0f))); // 29

	cube.addVertex(Vertex(glm::vec3(-0.5f,  0.5f, -0.5f),	glm::vec2(0.0f, 1.0f))); // 30
	cube.addVertex(Vertex(glm::vec3( 0.5f,  0.5f, -0.5f),	glm::vec2(1.0f, 1.0f))); // 31
	cube.addVertex(Vertex(glm::vec3( 0.5f,  0.5f,  0.5f),	glm::vec2(1.0f, 0.0f))); // 32
	cube.addVertex(Vertex(glm::vec3( 0.5f,  0.5f,  0.5f),	glm::vec2(1.0f, 0.0f))); // 33
	cube.addVertex(Vertex(glm::vec3(-0.5f,  0.5f,  0.5f),	glm::vec2(0.0f, 0.0f))); // 34
	cube.addVertex(Vertex(glm::vec3(-0.5f,  0.5f, -0.5f),	glm::vec2(0.0f, 1.0f))); // 35

	cube.move(glm::vec3(0.0, 0.5, 0.0));
	cube.scale(0.25);
	cube.finalize();
	camera.init(window, p);

	unsigned char* data;
	// Allocate the needed space.
	int width;
	int height;
	width = height = 128;

	data = new unsigned char[width * height * sizeof(unsigned char)];

	for(int i = 0; i < (int)(width * height * sizeof(unsigned char)); i++)
	{
		data[i] = 255;
	}

	// Generate white OpenGL texture.
	GLuint whiteTextureID;
	glGenTextures(1, &whiteTextureID);
	glBindTexture(GL_TEXTURE_2D, whiteTextureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glLineWidth(3);

	grid.init(Primitive::LINES, whiteTextureID);

	int w;
	int h;
	SDL_GetWindowSize(window, &w, &h);

	float x = 0;
	float y = 0;
	for (size_t j = 0; j < 250; j++) {
		x = 0;
		for (size_t i = 0; i < 250; i++) {
			grid.addVertex(Vertex(glm::vec3(-12.5 + x, -12.5 + y, 0.0), glm::vec2(1.0, 0.0)));
			grid.addVertex(Vertex(glm::vec3(-10.0 + x, -12.5 + y, 0.0), glm::vec2(1.0, 0.0)));

			grid.addVertex(Vertex(glm::vec3(-10.0 + x, -12.5 + y, 0.0), glm::vec2(1.0, 0.0)));
			grid.addVertex(Vertex(glm::vec3(-10.0 + x, -10.0 + y, 0.0), glm::vec2(1.0, 0.0)));

			grid.addVertex(Vertex(glm::vec3(-10.0 + x, -10.0 + y, 0.0), glm::vec2(1.0, 0.0)));
			grid.addVertex(Vertex(glm::vec3(-12.5 + x, -10.0 + y, 0.0), glm::vec2(1.0, 0.0)));

			grid.addVertex(Vertex(glm::vec3(-12.5 + x, -10.0 + y, 0.0), glm::vec2(1.0, 0.0)));
			grid.addVertex(Vertex(glm::vec3(-12.5 + x, -12.5 + y, 0.0), glm::vec2(1.0, 0.0)));
			x += 0.1;
		}
		y += 0.1;
	}
	grid.finalize();
	grid.rotate(glm::vec3(glm::radians(91.0f), glm::radians(90.0f), glm::radians(0.0f)));


	registerKeyboardEventCallback(SDL_SCANCODE_W, KeyEventType::HELD, [this]() {
		glm::vec3 dir = camera.cameraFront;
		dir.y = 0.0f;
		dir *= 0.125;
		camera.moveCamera(dir);
	});
	registerKeyboardEventCallback(SDL_SCANCODE_A, KeyEventType::HELD, [this]() {
		glm::vec3 dir = -glm::normalize(glm::cross(camera.cameraFront, camera.cameraUp));
		dir.y = 0.0f;
		dir *= 0.125;
		camera.moveCamera(dir);
	});
	registerKeyboardEventCallback(SDL_SCANCODE_S, KeyEventType::HELD, [this]() {
		glm::vec3 dir = -camera.cameraFront;
		dir.y = 0.0f;
		dir *= 0.125;
		camera.moveCamera(dir);
	});
	registerKeyboardEventCallback(SDL_SCANCODE_D, KeyEventType::HELD, [this]() {
		glm::vec3 dir = glm::normalize(glm::cross(camera.cameraFront, camera.cameraUp));
		dir.y = 0.0f;
		dir *= 0.125;
		camera.moveCamera(dir);
	});
	registerKeyboardEventCallback(SDL_SCANCODE_SPACE, KeyEventType::HELD, [this]() {
		glm::vec3 dir = camera.cameraUp;
		dir *= 0.025;
		camera.moveCamera(dir);
	});
	registerKeyboardEventCallback(SDL_SCANCODE_LSHIFT, KeyEventType::HELD, [this]() {
		glm::vec3 dir = -camera.cameraUp;
		dir *= 0.025;
		camera.moveCamera(dir);
	});
	registerKeyboardEventCallback(SDL_SCANCODE_RSHIFT, KeyEventType::HELD, [this]() {
		glm::vec3 dir = -camera.cameraUp;
		dir *= 0.025;
		camera.moveCamera(dir);
	});
	registerMouseMotionEventCallback([this](SDL_MouseMotionEvent&, glm::ivec2 /* pos */, glm::ivec2 delta) {
		if(isCursorDisabled()) {
			camera.rotateCamera(static_cast<double>(delta.x)/10, -static_cast<double>(delta.y)/10);
		}
	});
	registerWindowEventCallback([this](SDL_WindowEvent& ev) {
		switch(ev.event) {
			case SDL_WINDOWEVENT_RESIZED:
				camera.updateProjection();
		}
	});
	registerTimeoutCallback("ms_per_frame", 1000, [this]() {
		LOG_D("ms/frame = " << 1000/fps_avg << " | fps = " << fps_avg);
	}, true);
}

void CameraTestCore::render() {
	p->useProgram();
	gl.bind();

	cube.rotate(glm::vec3(glm::radians(0.1f), glm::radians(0.2f), glm::radians(-0.3f)));

	glUniform3fv(glGetUniformLocation(p->getPH(), "color"), 1, (float*)&cube_color[0]);
	camera.drawModel(cube);


	glUniform3fv(glGetUniformLocation(p->getPH(), "color"), 1, (float*)&line_color[0]);
	camera.drawModel(grid);

}

void CameraTestCore::tick() {

}

