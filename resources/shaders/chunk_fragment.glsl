#version 450 core
out vec4 FragColor;

// in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D texture_diffuse1;

void main() {
	FragColor = texture(texture_diffuse1, TexCoord);
}
