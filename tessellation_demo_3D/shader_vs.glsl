#version 410

layout(location = 0) in vec3 vPositions;
layout(location = 1) in vec3 vColors;

uniform mat4 MVP;
out vec4 ctr_point_out;


void main() {
	ctr_point_out = vec4(vPositions, 1);
	// ctr_point_out = MVP * vec4(vPositions, 1);
}
