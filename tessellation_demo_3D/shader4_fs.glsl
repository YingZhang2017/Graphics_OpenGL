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
in vec3 g_patch_distance;
in vec3 g_tri_distance;
in float g_primitive;

uniform vec3 object_color;
uniform vec3 light_color;

uniform vec3 light_position;
uniform vec3 diffuse_material;
uniform vec3 ambient_material;

uniform int draw_solid_line;

out vec4 fragment_colour;


float amplify (float d, float scale, float offset) {
	d = scale * d + offset;
	d = clamp(d, 0, 1);
	d = 1 - exp2(-2 * d * d);
	return d;
}

void main () {

	// ambient
	float ambient_strength = 0.2f;
	vec3 ambient = ambient_strength * light_color;

	// diffuse
	vec3 norm = normalize(g_face_normal);
	float diff = abs(dot(norm, light_position));
	vec3 diffuse = diff * light_color;

  // specular
	vec3 H = normalize(light_position + vec3(0, 0, 1));
	float spec = abs(dot(norm, H));
	float shininess = 0.1f;
	vec3 specular_material = vec3(0.2f, 0.2f, 0.2f);
	vec3 specular = pow(spec, shininess) * specular_material;

	vec3 final;

	if (draw_solid_line == 1) {
		float d1 = min(min(g_tri_distance.x, g_tri_distance.y), g_tri_distance.z);
		float d2 = min(min(g_patch_distance.x, g_patch_distance.y), g_patch_distance.z);
		d1 = 1 - amplify(d1, 50, -0.5);
		d2 = amplify(d2, 50, -0.5);
		final = d2 * object_color + d1 * d2 * object_color;
	} else {
		final = (ambient + diffuse + specular) * object_color;
	}
		fragment_colour = vec4(final, 1.0);

}
