#version 410

// number of CPs in patch
layout (vertices = 4) out;
uniform float tess_fac_outer = 1.0; // controlled by keyboard buttons

void main () {
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;

	// Calculate the tessellation levels
	gl_TessLevelOuter[0] = 1.0; // how many curve to generate
	gl_TessLevelOuter[1] = tess_fac_outer; // times to subdivide
}
