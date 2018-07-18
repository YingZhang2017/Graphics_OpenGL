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

	float d1 = min(min(g_patch_distance.x, g_patch_distance.y), g_patch_distance.z);
	float d2 = min(min(g_tri_distance.x, g_tri_distance.y), g_tri_distance.z);
	final =  amplify (d1, 40, -0.4) * amplify (d2, 60, -0.6) * object_color;

	fragment_colour = vec4(final, 1.0);

}
