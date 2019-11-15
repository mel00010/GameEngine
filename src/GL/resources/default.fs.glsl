#version 450

out vec4 FragColor;

//in vec3 Normal;
in vec4 Color;
//in vec4 Secondary_color;
//in vec3 Tangent;
//in vec3 Bitangent;
in vec2 Tex_coord0;
//in vec2 Tex_coord1;
//in vec2 Tex_coord2;
//in vec2 Tex_coord3;
//in vec2 Tex_coord4;
//in vec2 Tex_coord5;
//in vec2 Tex_coord6;
//in vec2 Tex_coord7;
//in float Fog_coord;

// texture samplers
uniform sampler2D texture_diffuse0;


uniform vec3 color;

void main() {
	FragColor = texture(texture_diffuse0, Tex_coord0) * Color * vec4(color, 1.0f);
	
	//FragColor = texture(text, TexCoord);
}