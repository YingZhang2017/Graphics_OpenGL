#version 410

layout (triangles, equal_spacing, cw) in;
in vec3 tc_position[];
in vec3 tc_normal[];

out vec3 position_eye;	// frag position
out vec3 normal_eye;   // normal

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main () {
	// x,y,z is three corners. z should be ignore if is quad
	vec3 p0 = gl_TessCoord.x * tc_position[0];
	vec3 p1 = gl_TessCoord.y * tc_position[1];
	vec3 p2 = gl_TessCoord.z * tc_position[2];
	vec3 pos = p0 + p1 + p2;

	position_eye = vec3 (viewMatrix * modelMatrix * vec4 (pos, 1.0));
	normal_eye = vec3 (viewMatrix * modelMatrix * vec4(0.0, 0.0, 1.0, 0.0));
	gl_Position = projectionMatrix * vec4(position_eye, 1.0);
}
