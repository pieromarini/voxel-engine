#version 450 core
in vec3 aPos;
in vec3 aNormal;
in vec2 aTexCoord;

out vec3 fragPos;
out vec2 TexCoord;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	fragPos = vec3(model * vec4(aPos, 1.0));
	gl_Position = projection * view * vec4(fragPos, 1.0f);
	TexCoord = aTexCoord;

	// NOTE: This should be computed in the CPU and sent to the shader
	// Normal = mat3(transpose(inverse(model))) * aNormal;

	Normal = aNormal;
}
