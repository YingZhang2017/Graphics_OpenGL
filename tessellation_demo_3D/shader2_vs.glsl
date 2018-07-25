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

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;

out vec3 v_position;
out vec3 v_normal;

void main() {

	v_position = vertex_position;
	v_normal = vertex_normal;
}
