#version 450

layout(location = 0) in vec4 position;
layout(location = 2) in vec4 normal;
layout(location = 3) in vec4 color;
layout(location = 4) in vec4 secondary_color;
layout(location = 5) in vec4 tangent;
layout(location = 6) in vec4 bitangent;
layout(location = 7) in vec4 tex_coord0;
layout(location = 8) in vec4 tex_coord1;
layout(location = 9) in vec4 tex_coord2;
layout(location = 10) in vec4 tex_coord3;
layout(location = 11) in vec4 tex_coord4;
layout(location = 12) in vec4 tex_coord5;
layout(location = 13) in vec4 tex_coord6;
layout(location = 14) in vec4 tex_coord7;
layout(location = 15) in vec4 tex_coord8;
layout(location = 16) in vec4 tex_coord9;
layout(location = 17) in vec4 tex_coord10;
layout(location = 18) in vec4 tex_coord11;
layout(location = 19) in vec4 tex_coord12;
layout(location = 20) in vec4 tex_coord13;
layout(location = 21) in vec4 tex_coord14;
layout(location = 22) in vec4 tex_coord15;
layout(location = 23) in float fog_coord;

//out vec4 Normal;
//out vec4 Color;
//out vec4 Secondary_color;
//out vec4 Tangent;
//out vec4 Bitangent;
out vec4 Tex_coord0;
//out vec4 Tex_coord1;
//out vec4 Tex_coord2;
//out vec4 Tex_coord3;
//out vec4 Tex_coord4;
//out vec4 Tex_coord5;
//out vec4 Tex_coord6;
//out vec4 Tex_coord7;
//out vec4 Tex_coord8;
//out vec4 Tex_coord9;
//out vec4 Tex_coord10;
//out vec4 Tex_coord11;
//out vec4 Tex_coord12;
//out vec4 Tex_coord13;
//out vec4 Tex_coord14;
//out vec4 Tex_coord15;
//out float Fog_coord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	// note that we read the multiplication from right to left
	gl_Position = projection * view * model * position;
	
	//Normal = normal;
	//Color = color;
	//Secondary_color = secondary_color;
	//Tangent = tangent;
	//Bitangent = bitangent;
	Tex_coord0 = tex_coord0;
	//Tex_coord1 = tex_coord1;
	//Tex_coord2 = tex_coord2;
	//Tex_coord3 = tex_coord3;
	//Tex_coord4 = tex_coord4;
	//Tex_coord5 = tex_coord5;
	//Tex_coord6 = tex_coord6;
	//Tex_coord7 = tex_coord7;
	//Tex_coord8 = tex_coord8;
	//Tex_coord9 = tex_coord9;
	//Tex_coord10 = tex_coord10;
	//Tex_coord11 = tex_coord11;
	//Tex_coord12 = tex_coord12;
	//Tex_coord13 = tex_coord13;
	//Tex_coord14 = tex_coord14;
	//Tex_coord15 = tex_coord15;
	//Fog_coord = fog_coord;
}
