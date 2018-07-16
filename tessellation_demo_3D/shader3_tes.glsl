#version 410

layout (triangles, equal_spacing, cw) in;
in vec3 tc_position[];
in vec3 tc_normal[];

out vec3 frag_pos;
out vec3 frag_normal;


uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main () {
	// x,y,z is three corners. z should be ignore if is quad
	vec3 p1 = gl_TessCoord.x * tc_position[0];
	vec3 p2 = gl_TessCoord.y * tc_position[1];
	vec3 p3 = gl_TessCoord.z * tc_position[2];
	vec3 pos = normalize(p1 + p2 + p3);
	frag_pos = vec3(modelMatrix * vec4(pos, 1.0));


	vec3 n1 = gl_TessCoord.x * tc_normal[0];
	vec3 n2 = gl_TessCoord.y * tc_normal[1];
	vec3 n3 = gl_TessCoord.z * tc_normal[2];
	vec3 nor = normalize(n1 + n2 + n3);
	frag_normal = mat3(transpose(inverse(modelMatrix))) * nor;;


	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(pos, 1.0);


}
