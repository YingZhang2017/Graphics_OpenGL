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

	vec3 n0 = gl_TessCoord.x * tc_normal[0];
	vec3 n1 = gl_TessCoord.y * tc_normal[1];
	vec3 n2 = gl_TessCoord.z * tc_normal[2];
	vec3 nor = n0 + n1 + n2;
	normal_eye = vec3 (viewMatrix * modelMatrix * vec4(nor, 0.0));

	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(pos, 1.0);
}
