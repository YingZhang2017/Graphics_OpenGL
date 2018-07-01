#version 410
layout (isolines) in;
out vec3 colour;

void main () {
	vec4 p0 = gl_in[0].gl_Position;
	vec4 p1 = gl_in[1].gl_Position;
	vec4 p2 = gl_in[2].gl_Position;
	vec4 p3 = gl_in[3].gl_Position;

	float u = gl_TessCoord.x;
	// bezier functions
	float b0 = (1.0 - u) * (1.0 - u) * (1.0 - u);
	float b1 = 3.0 * u * (1.0 - u) * (1.0 - u);
	float b2 = 3.0 * u * u * (1.0 - u);
	float b3 = u * u * u;

	gl_Position = b0 * p0 + b1 * p1 + b2 * p2 + b3 * p3;

	// use coords as colours in the frag shader
	colour.rbg = gl_TessCoord.xyz;
}
