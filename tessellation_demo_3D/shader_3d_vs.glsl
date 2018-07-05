#version 410

layout(location = 0) in vec3 vPositions;
// layout(location = 1) in vec4 vColors;

uniform mat4 MVP;

void main() {
	gl_Position = MVP * vec4(vPositions, 1);
}
