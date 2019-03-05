#version 450

out vec4 oColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D text;
uniform vec3 color;

void main() {
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	//FragColor = texture(texture1, TexCoord) * vec4(ourColor.x, ourColor.y, ourColor.z, 1.0f);
	
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoord).r);
	oColor = vec4(color, 1.0) * sampled;
	//FragColor = vec4(1.0, 1.0, 0.0, 1.0);
}