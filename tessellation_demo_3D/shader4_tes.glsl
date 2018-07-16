#version 410

layout (triangles, equal_spacing, cw) in;
in vec3 tc_position[];

out vec3 te_position;
out vec3 te_patch_distance;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main () {
	vec3 p0 = gl_TessCoord.x * tc_position[0];
	vec3 p1 = gl_TessCoord.y * tc_position[1];
	vec3 p2 = gl_TessCoord.z * tc_position[2];
	te_position = normalize(p0 + p1 + p2);
	te_patch_distance = gl_TessCoord;
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(te_position, 1.0);
}
