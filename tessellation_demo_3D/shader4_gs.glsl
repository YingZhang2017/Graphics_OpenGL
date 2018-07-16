#version 410

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec3 te_position[];
in vec3 te_patch_distance[];

out vec3 g_face_normal;
out vec3 g_patch_distance;
out vec3 g_tri_distance;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;

void main() {
  mat4 nm = transpose(inverse(viewMatrix * modelMatrix));
  mat3 normalMatrix;
  normalMatrix[0] = vec3(nm[0].xyz);
  normalMatrix[1] = vec3(nm[1].xyz);
  normalMatrix[2] = vec3(nm[2].xyz);

  vec3 d0 = te_position[1] - te_position[0];
  vec3 d1 = te_position[2] - te_position[0];
  g_face_normal = normalMatrix * normalize(cross(d0, d1));

  g_patch_distance = te_patch_distance[0];
  g_tri_distance = vec3(1, 0, 0);
  gl_Position = gl_in[0].gl_Position;
  EmitVertex();

  g_patch_distance = te_patch_distance[1];
  g_tri_distance = vec3(0, 1, 0);
  gl_Position = gl_in[1].gl_Position;
  EmitVertex();

  g_patch_distance = te_patch_distance[2];
  g_tri_distance = vec3(0, 0, 1);
  gl_Position = gl_in[2].gl_Position;
  EmitVertex();

  EndPrimitive();
}
