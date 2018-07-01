#version 410

// number of CPs in patch
layout (vertices = 1) out;

uniform float tess_fac_inner = 1.0;
uniform float tess_fac_outer = 1.0;

uniform mat4 projection_mat, view_mat, model_mat;
in vec3 position_eye, normal_eye;

// from vs
in vec3 ctr_point_out[];

// to tes
out vec3 eva_point_out[];



void main () {
	eva_point_out[gl_InvocationID] = ctr_point_out[gl_InvocationID];

	// Calculate the tessellation levels
	gl_TessLevelInner[0] = tess_fac_inner; // number of nested primitives to generate
	gl_TessLevelOuter[0] = tess_fac_outer; // times to subdivide first side
	gl_TessLevelOuter[1] = tess_fac_outer; // times to subdivide second side
	gl_TessLevelOuter[2] = tess_fac_outer; // times to subdivide third side
}
