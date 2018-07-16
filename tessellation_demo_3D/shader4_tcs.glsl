#version 410

// number of CPs in patch
layout (vertices = 4) out;

// from vs
in vec3 v_position[];
in vec3 v_normal[];

// to tes
out vec3 tc_position[];
out vec3 tc_normal[];

uniform float tess_fac_inner = 1.0;
uniform float tess_fac_outer = 1.0;

void main () {
	tc_position[gl_InvocationID] = v_position[gl_InvocationID];
	tc_normal[gl_InvocationID] = v_normal[gl_InvocationID];

	// Calculate the tessellation levels
	gl_TessLevelInner[0] = tess_fac_inner; // number of nested primitives to generate
	gl_TessLevelInner[1] = tess_fac_inner; // number of nested primitives to generate

	gl_TessLevelOuter[0] = tess_fac_outer; // times to subdivide first side
	gl_TessLevelOuter[1] = tess_fac_outer; // times to subdivide second side
	gl_TessLevelOuter[2] = tess_fac_outer; // times to subdivide third side
	gl_TessLevelOuter[3] = tess_fac_outer; // times to subdivide third side

}
