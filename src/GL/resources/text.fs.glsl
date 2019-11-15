#version 450

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D glyph;

uniform vec3 color;

void main() {
	FragColor = vec4(1, 1, 1, texture(glyph, TexCoords).r) * vec4(color, 1.0f);
}