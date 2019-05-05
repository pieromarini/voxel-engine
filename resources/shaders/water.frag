#version 430 core

in vec2 texCoords;
out vec4 out_Color;

uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;

void main() {

	vec4 reflectColor = texture(reflectionTexture, texCoords);
	vec4 refractionColor = texture(refractionTexture, texCoords);

	out_Color = mix(reflectColor, refractionColor, 0.5);
}
