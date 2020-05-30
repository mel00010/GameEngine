#version 450

out vec4 FragColor;

in vec4 Color;
in vec3 TexCoords;

// texture samplers
uniform samplerCube cube_map;

uniform vec3 color;

void main() {
  FragColor = texture(cube_map, TexCoords) * Color * vec4(color, 1.0f);
}