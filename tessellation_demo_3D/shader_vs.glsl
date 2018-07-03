#version 410

in vec3 vert_loc;
out vec3 ctr_point_out;

void main() {
	ctr_point_out = vert_loc;
}
