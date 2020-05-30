#version 450

out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube cube_map;

void main() {
  FragColor = texture(cube_map, TexCoords);
  // FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}