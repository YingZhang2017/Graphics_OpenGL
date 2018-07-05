//refer: "Anton's OpenGL 4 Tutorials", t018	- will to be modified later

#version 410

in vec3 position_eye, normal_eye, texcoord_eye;
uniform mat4 view_mat;
out vec4 fragment_colour;

// fixed point light properties
// set fixed light position
vec3 light_position_world  = vec3(0.5, 0.5, 2.5);
// set specular light color
vec3 Ls = vec3(1.0, 1.0, 1.0);
// set diffuse light color
vec3 Ld = vec3(0.6, 0.7, 0.8);
// set ambient light color
vec3 La = vec3(0.3, 0.3, 0.3);

// surface reflectance
// set specular light reflect
vec3 Ks = vec3(1.0, 1.0, 1.0);
// set diffuse light reflect
vec3 Kd = vec3(1.0, 0.6, 0.1);
// set ambient light color
vec3 Ka = vec3(1.0, 1.0, 1.0);
// set spec exponent
float specular_exponent = 1000.0;

void main () {
	// ambient intensity
	vec3 Ia = La * Ka;

	/* Point Light */
	vec3 light_position_eye = vec3 (view_mat * vec4 (light_position_world, 1.0));
	vec3 distance_to_light_eye = light_position_eye - position_eye;
	vec3 direction_to_light_eye = normalize (distance_to_light_eye);

	/* Spotlight */
	vec3 spot_direction = normalize(vec3 (0.0, 0.0, -1.0));
	float spot_arc = 0.906; // cos(25 degrees)
	float spot_dot = dot (spot_direction, -direction_to_light_eye);
	float spot_factor = (spot_dot - spot_arc) / (1.0 - spot_arc);
	spot_factor = clamp (spot_factor, 0.0, 1.0);

	// diffuse intensity
	float dot_prod = dot (direction_to_light_eye, normal_eye);
	dot_prod = max (dot_prod, 0.0);
	vec3 Id = Ld * Kd * dot_prod;
	Id *= spot_factor;

	// specular intensity
	vec3 surface_to_viewer_eye = normalize (-position_eye);
	vec3 half_way_eye = normalize (surface_to_viewer_eye + direction_to_light_eye);
	float dot_prod_specular = max (dot (half_way_eye, normal_eye), 0.0);
	float specular_factor = pow (dot_prod_specular, specular_exponent);

	vec3 Is = Ls * Ks * specular_factor;
	Is *= spot_factor;

	// final colour
	fragment_colour = vec4 (Is + Id + Ia, 1.0);
}
