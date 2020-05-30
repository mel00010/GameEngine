#version 450

layout(location = 0) in vec3 position;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec4 color;
layout(location = 4) in vec4 secondary_color;
layout(location = 5) in vec3 tangent;
layout(location = 6) in vec3 bitangent;
layout(location = 7) in vec2 tex_coord0;
layout(location = 8) in vec2 tex_coord1;
layout(location = 9) in vec2 tex_coord2;
layout(location = 10) in vec2 tex_coord3;
layout(location = 11) in vec2 tex_coord4;
layout(location = 12) in vec2 tex_coord5;
layout(location = 13) in vec2 tex_coord6;
layout(location = 14) in vec2 tex_coord7;
layout(location = 15) in float fog_coord;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
  // note that we read the multiplication from right to left
  gl_Position = projection * view * model * vec4(position, 1.0);

  TexCoords = tex_coord0;
}
