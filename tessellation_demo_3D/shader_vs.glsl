#version 410

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;

out vec3 v_position;
out vec3 v_normal;
// uniform mat4 modelMatrix, viewMatrix, projectionMatrix;

void main() {
	/*
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex_position, 1.0f);
	v_position = vec3(modelMatrix * vec4(vertex_position, 1.0f));
	v_normal = mat3(transpose(inverse(modelMatrix))) * vertex_normal;
	*/

	
	v_position = vertex_position;
	v_normal = vertex_normal;
}
