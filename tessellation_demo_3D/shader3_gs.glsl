/*
	Author: Ying Zhang,
	July, 2018

	reference sources:
	1. UNH cs770 base code of demos, R.Daniel.Bergeron

	2. Accompanies written series "Anton's OpenGL 4 Tutorials"
		 Copyright Dr Anton Gerdelan, Trinity College Dublin, Ireland.
		 Demo_22: Gemo_shaders
		 Demo_23: Tessellation_shaders
		 https://github.com/capnramses/antons_opengl_tutorials_book

	3. OGLev Modern OpenGL Tutorials
		 Turorial 30: Basic Tessellation
		 http://ogldev.atspace.co.uk/www/tutorial30/tutorial30.html
		 Turirial 31: PN Triangles Tessellation
		 http://ogldev.atspace.co.uk/www/tutorial31/tutorial31.html

	4. Oregon State University, Mike Bailey, Tessellation Shaders,
		 http://web.engr.oregonstate.edu/~mjb/cs519/Handouts/tessellation.1pp.pdf

	5. The Little Grasshopper, Graphics Programming Tips
		 Triangle Tessellation with OpenGL 4.0
		 http://prideout.net/blog/?p=48
		 Quad Tessellation with OpenGL 4.0
		 http://prideout.net/blog/?p=49

	6. GL-tessellatiuon-example
		 https://github.com/slime73/GL-tessellation-example

	7. Learn OPENGL
		 Basic Lighting, https://learnopengl.com/Lighting/Basic-Lighting

	8. opengl-tutorial
		 Tutorial 8: Basic Shading
	 http://www.opengl-tutorial.org/beginners-tutorials/tutorial-8-basic-shading/
*/

#version 410

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec3 te_position[];
in vec3 te_patch_distance[];

out vec3 g_face_normal;
out vec3 g_tri_distance;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;

void main() {
  // set normal matrix
  mat4 nm = transpose(inverse(viewMatrix * modelMatrix));
  mat3 normalMatrix;
  normalMatrix[0] = vec3(nm[0].xyz);
  normalMatrix[1] = vec3(nm[1].xyz);
  normalMatrix[2] = vec3(nm[2].xyz);

  vec3 d0 = te_position[1] - te_position[0];
  vec3 d1 = te_position[2] - te_position[0];
  g_face_normal = normalMatrix * normalize(cross(d0, d1));

  g_tri_distance = vec3(1, 0, 0);
  gl_Position = gl_in[0].gl_Position;
  EmitVertex();

  g_tri_distance = vec3(0, 1, 0);
  gl_Position = gl_in[1].gl_Position;
  EmitVertex();

  g_tri_distance = vec3(0, 0, 1);
  gl_Position = gl_in[2].gl_Position;
  EmitVertex();

  EndPrimitive();
}
