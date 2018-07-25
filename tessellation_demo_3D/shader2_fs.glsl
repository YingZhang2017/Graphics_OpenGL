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

in vec3 position_eye;
in vec3 normal_eye;
in vec3 colour;


uniform vec3 object_color;
uniform vec3 light_color;
uniform vec3 light_position;
uniform vec3 view_position;

out vec4 fragment_colour;

void main () {
	// ambient
	float ambient_strength = 0.8f;
	vec3 ambient = ambient_strength * light_color;

	// diffuse
	vec3 norm = normalize(normal_eye);
	vec3 light_direction = normalize(light_position - position_eye);
	float diff = max(dot(norm, light_direction), 0.0);
	vec3 diffuse = diff * light_color;

	// specular
	float specular_strength = 0.5;
	vec3 view_direction = normalize(view_position - position_eye);
	vec3 reflect_direction = reflect(-light_direction, norm);
	float spec = pow(max(dot(view_direction, reflect_direction), 0.0), 32);
	vec3 specular = specular_strength * spec * object_color;

	vec3 final = (ambient + diffuse + specular) * object_color;
	fragment_colour = vec4(final, 1.0);

}
