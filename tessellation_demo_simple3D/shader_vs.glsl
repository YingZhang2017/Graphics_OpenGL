//refer: "Anton's OpenGL 4 Tutorials", t018	- will to be modified later
#version 410

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_normal;
layout (location = 2) in vec2 vertex_texcord;

out vec3 v_position, v_normal;
out vec2 v_texcord;

void main () {
	v_position = vertex_position;
	v_normal = vertex_normal;
	v_texcord = vertex_texcord;
}
