#version 410

layout (triangles, equal_spacing, ccw) in;
in vec4 eva_point_out[];

void main () {
	// x,y,z is three corners. z should be ignore if is quad
	vec4 p0 = gl_TessCoord.x * eva_point_out[0];
	vec4 p1 = gl_TessCoord.y * eva_point_out[1];
	vec4 p2 = gl_TessCoord.z * eva_point_out[2];
	vec4 pos = p0 + p1 + p2;

	gl_Position = pos;
}
