#version 410

in vec3 vp_loc;
out vec3 controlpoint_wor;

void main() {
	// control points out == vertex points in
	controlpoint_wor = vp_loc;
}
