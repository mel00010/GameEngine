/******************************************************************************
 * DVD.cpp
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

#include "DVD.hpp"

#include <Log.hpp>
#include <Texture.hpp>
#include <Resources.hpp>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtx/color_space.hpp>

using namespace GameEngine;

DVD::DVD(ProgramRef _p) : p(_p) {
	dvd_texture = Texture().loadTexture(Resources[static_cast<size_t>(ResourceID::DVD)]);
	updateLogoColor();

	p->useProgram();

	gl.init();
	gl.bind();
	gl.allocate(sizeof(Vertex) * 4, sizeof(Vertex) * 4);
	// vertex
	gl.addVertexPointer(0, 2, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, pos));
	gl.addVertexPointer(1, 2, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex));


	delta_vec = glm::vec3(glm::circularRand(1.0), 0.0);
}

bool DVD::isAtWindowEdge(WindowEdge edge, double length, glm::dvec2 offset) {
	switch(edge) {
		case RIGHT:		return length > (offset.x - translate_vec.x);
		case LEFT:		return length > (offset.x + translate_vec.x);
		case TOP:		return length > (offset.y - translate_vec.y);
		case BOTTOM:	return length > (offset.y + translate_vec.y);
	}
	return false;
}

void DVD::updateLogoColor() {
	glm::vec3 logo_color_hsv = glm::vec3(glm::linearRand(0.0, 360.0), 1.0, 1.0);
	logo_color = glm::rgbColor(logo_color_hsv);
}

void DVD::draw(double& fps) {
	p->useProgram();
	gl.bind();

	if(fps == 0) {
		fps = 60;
	}

	// bind textures on corresponding texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, dvd_texture);
	Vertex vertices[] = {
				// positions 				// texture coords
		Vertex(	glm::vec2( 0.5f,  0.5f),	glm::vec2(1.0f, 1.0f)), // top right
		Vertex(	glm::vec2( 0.5f, -0.5f),	glm::vec2(1.0f, 0.0f)), // bottom right
		Vertex(	glm::vec2(-0.5f, -0.5f),	glm::vec2(0.0f, 0.0f)), // bottom left
		Vertex(	glm::vec2(-0.5f,  0.5f),	glm::vec2(0.0f, 1.0f)), // top left
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(indices), indices);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	// create transformations
	glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

	transform = glm::translate(transform, translate_vec);
	transform = glm::scale(transform, 0.5f / glm::vec3(scale, 1.0));

	glm::vec3 right_surface = glm::vec3(1.0, 0.0, 0.0);
	glm::vec3 left_surface = glm::vec3(1.0, 0.0, 0.0);
	glm::vec3 top_surface = glm::vec3(0.0, 1.0, 0.0);
	glm::vec3 bottom_surface = glm::vec3(0.0, 1.0, 0.0);

	right_surface += glm::vec3(glm::diskRand(0.05f), 0.0f);
	left_surface += glm::vec3(glm::diskRand(0.05f), 0.0f);
	top_surface += glm::vec3(glm::diskRand(0.05f), 0.0f);
	bottom_surface += glm::vec3(glm::diskRand(0.05f), 0.0f);

	glm::dvec2 offset = (scale - glm::dvec2(0.235, 0.115)) / scale;

	glm::vec3 scale_factor = glm::vec3(speed / (scale * fps * 4.0), 0.0);
	double length = glm::length(delta_vec * scale_factor);

	bool reflected = false;
	if(isAtWindowEdge(RIGHT, length, offset)) {
		delta_vec = glm::normalize(glm::reflect(delta_vec, right_surface));
		translate_vec.x =  offset.x - length;
		reflected = true;
	} if(isAtWindowEdge(LEFT, length, offset)) {
		delta_vec = glm::normalize(glm::reflect(delta_vec, left_surface));
		translate_vec.x = -offset.x + length;
		reflected = true;
	} if(isAtWindowEdge(TOP, length, offset)) {
		delta_vec = glm::normalize(glm::reflect(delta_vec, top_surface));
		translate_vec.y =  offset.y - length;
		reflected = true;
	} if(isAtWindowEdge(BOTTOM, length, offset)) {
		delta_vec = glm::normalize(glm::reflect(delta_vec, bottom_surface));
		translate_vec.y = -offset.y + length;
		reflected = true;
	}
	if(reflected) {
		updateLogoColor();
	}
	translate_vec += delta_vec * scale_factor;

	glUniform3fv(glGetUniformLocation(p->getPH(), "color"), 1, (float*)glm::value_ptr(logo_color));

	// get matrix's uniform location and set matrix
	unsigned int transformLoc = glGetUniformLocation(p->getPH(), "projection");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);

	// render container
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
