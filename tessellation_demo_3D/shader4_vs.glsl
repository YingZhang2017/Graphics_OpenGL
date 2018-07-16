#version 410

layout(location = 0) in vec3 vertex_position;
out vec3 v_position;

void main() {

	v_position = vertex_position.xyz;

}
