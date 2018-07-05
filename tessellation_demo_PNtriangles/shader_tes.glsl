#version 410

layout (triangles, equal_spacing, cw) in;
uniform mat4 projection_mat, view_mat, model_mat;

in vec3 tc_position[];
in vec3 tc_normal[];
in vec2 tc_texcord[];
out vec3 position_eye, normal_eye, texcoord_eye;
// out vec3 colour;

void main () {
	// x,y,z is three corners. z should be ignore if is quad
	vec3 p0 = gl_TessCoord.x * tc_position[0];
	vec3 p1 = gl_TessCoord.y * tc_position[1];
	vec3 p2 = gl_TessCoord.z * tc_position[2];
	vec3 pos = p0 + p1 + p2;

	// gl_Position = vec4 (pos, 1.0);
	position_eye = vec3 (view_mat * model_mat * vec4 (pos, 1.0));
	//normal_eye = vec3 (view_mat * model_mat * vec4 (tc_normal, 0.0));
	//texcoord_eye = tc_texcord;

	normal_eye = vec3 (view_mat * model_mat * vec4(0.0, 0.0, 1.0, 0.0));
	texcoord_eye = vec3(0.0, 0.0, 0.0);

	gl_Position = projection_mat * vec4 (position_eye, 1.0);

	// use coords as colours in the frag shader
	// colour.rbg = gl_TessCoord.xyz;
}
