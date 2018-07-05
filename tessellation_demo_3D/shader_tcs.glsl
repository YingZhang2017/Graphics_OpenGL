#version 410

// number of CPs in patch
layout (vertices = 4) out;

// from vs
in vec4 ctr_point_out[];

// to tes
out vec4 eva_point_out[];

uniform float tess_fac_inner = 1.0;
uniform float tess_fac_outer = 1.0;

void main () {
	eva_point_out[gl_InvocationID] = ctr_point_out[gl_InvocationID];

	// Calculate the tessellation levels
	gl_TessLevelInner[0] = tess_fac_inner; // number of nested primitives to generate
	gl_TessLevelInner[1] = tess_fac_inner; // number of nested primitives to generate


	gl_TessLevelOuter[0] = tess_fac_outer; // times to subdivide first side
	gl_TessLevelOuter[1] = tess_fac_outer; // times to subdivide second side
	gl_TessLevelOuter[2] = tess_fac_outer; // times to subdivide third side
	gl_TessLevelOuter[3] = tess_fac_outer; // times to subdivide third side

}
