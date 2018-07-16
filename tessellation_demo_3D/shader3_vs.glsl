#version 410

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;

out vec3 v_position;
out vec3 v_normal;

void main() {

	v_position = vertex_position;
	v_normal = vertex_normal;
}
