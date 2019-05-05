#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Set this as uniform.
const vec4 plane = vec4(0, -1, 0, 80);

void main() {
	vec4 worldPos = model * vec4(position, 1.0);
	gl_ClipDistance[0] = dot(worldPos, plane);
	TexCoords = texCoords;
	gl_Position = projection * view * worldPos;
}
