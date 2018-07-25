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

in vec3 g_face_normal;
in vec3 g_tri_distance;
in float g_primitive;

uniform vec3 object_color;
uniform vec3 light_color;

uniform vec3 light_position;
uniform vec3 diffuse_material;
uniform vec3 ambient_material;

uniform vec3 view_position;

out vec4 fragment_colour;


float amplify (float d, float scale, float offset) {
	d = scale * d + offset;
	d = clamp(d, 0, 1);
	d = 1 - exp2(-2 * d * d);
	return d;
}

void main () {
	// ambient
	float ambient_strength = 0.5f;
 	vec3 ambient = ambient_strength * ambient_material * light_color;

	// diffuse
	vec3 norm = normalize(g_face_normal);
	vec3 light_dir = normalize(light_position - g_tri_distance);
	float diff = max(dot(norm, light_dir), 0.0);
	vec3 diffuse = diff * diffuse_material * light_color;

	vec3 final = ambient + diffuse;

	float dist = min(min(g_tri_distance.x, g_tri_distance.y), g_tri_distance.z);
	final =  amplify (dist, 50, -0.4) * object_color;
	fragment_colour = vec4(final, 1.0);

}
