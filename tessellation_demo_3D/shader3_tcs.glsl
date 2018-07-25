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

// number of CPs in patch
layout (vertices = 3) out;

// from vs
in vec3 v_position[];

// to tes
out vec3 tc_position[];

uniform float tess_fac_inner = 1.0;
uniform float tess_fac_outer = 1.0;

void main () {
	tc_position[gl_InvocationID] = v_position[gl_InvocationID];

	// Calculate the tessellation levels
	gl_TessLevelInner[0] = tess_fac_inner; // number of nested primitives to generate
	gl_TessLevelOuter[0] = tess_fac_outer; // times to subdivide first side
	gl_TessLevelOuter[1] = tess_fac_outer; // times to subdivide second side
	gl_TessLevelOuter[2] = tess_fac_outer; // times to subdivide third side

}
