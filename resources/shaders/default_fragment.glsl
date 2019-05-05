#version 450 core
out vec4 FragColor;

in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;

void main() {
	FragColor = mix(texture(texture_diffuse1, TexCoord), 
					texture(texture_diffuse2, TexCoord), 0.2);
}
