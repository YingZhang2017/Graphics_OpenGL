#version 410

layout (triangles, equal_spacing, ccw) in;
in vec3 eva_point_out[];
out vec3 colour;

void main () {
	// x,y,z is three corners. z should be ignore if is quad
	vec3 p0 = gl_TessCoord.x * eva_point_out[0];
	vec3 p1 = gl_TessCoord.y * eva_point_out[1];
	vec3 p2 = gl_TessCoord.z * eva_point_out[2];
	vec3 pos = p0 + p1 + p2;

	gl_Position = vec4 (pos, 1.0);

	// use coords as colours in the frag shader
	colour.rbg = gl_TessCoord.xyz;
}
