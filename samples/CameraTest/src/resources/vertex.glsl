#version 450

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	// note that we read the multiplication from right to left
	gl_Position = projection * view * model * vec4(pos, 1.0);
	TexCoord = tex;
}
