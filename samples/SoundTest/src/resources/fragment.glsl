#version 450

out vec4 FragColor;

in vec4 Normal;
in vec4 Color;
in vec4 Secondary_color;
in vec4 Tangent;
in vec4 Bitangent;
in vec2 Tex_coord0;
in vec4 Tex_coord1;
in vec4 Tex_coord2;
in vec4 Tex_coord3;
in vec4 Tex_coord4;
in vec4 Tex_coord5;
in vec4 Tex_coord6;
in vec4 Tex_coord7;
in float Fog_coord;

// texture samplers
uniform sampler2D texture_diffuse0;


uniform vec3 color;

void main() {
	FragColor = texture(texture_diffuse0, Tex_coord0) * vec4(color, 1.0f);
	
	//FragColor = texture(text, TexCoord);
}