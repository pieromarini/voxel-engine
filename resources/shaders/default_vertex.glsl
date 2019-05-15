#version 450 core
in vec3 aPos;
// in vec3 aNormal;
in vec2 aTexCoord;

// out vec3 Normal;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	// Normal = aNormal;
	TexCoord = aTexCoord;
}
