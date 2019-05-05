#version 450 core
in vec3 aPos;
in vec2 aTexCoord;
in vec3 aNormal;
in vec3 aOffset;

out vec2 TexCoord;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * model * vec4(aPos + aOffset, 1.0f);
	TexCoord = aTexCoord;
	Normal = aNormal;
}
