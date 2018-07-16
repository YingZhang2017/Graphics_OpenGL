#version 410

layout (quads) in;
in vec3 tc_position[];
in vec3 tc_normal[];

out vec3 position_eye;	// frag position
out vec3 normal_eye;   // normal
out vec3 colour;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main () {
	vec3 p1 = mix(tc_position[0], tc_position[1], gl_TessCoord.x);
	vec3 p2 = mix(tc_position[2], tc_position[3], gl_TessCoord.x);
	//vec3 pos = normalize(mix(p1, p2, gl_TessCoord.y));
	vec3 pos = mix(p1, p2, gl_TessCoord.y);
	position_eye = vec3 (viewMatrix * modelMatrix * vec4 (pos, 1.0));
	normal_eye = normalize(position_eye);

	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(pos, 1.0);
}
