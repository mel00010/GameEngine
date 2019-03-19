#version 450

out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D text;
uniform vec3 color;

void main() {
	FragColor = texture(text, TexCoord) * vec4(color.xyz, 1.0f);
	
	//FragColor = texture(text, TexCoord);
}