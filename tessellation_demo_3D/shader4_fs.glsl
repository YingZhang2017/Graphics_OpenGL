#version 410

in vec3 g_face_normal;
in vec3 g_patch_distance;
in vec3 g_tri_distance;
in vec3 normal_eye;
in float g_primitive;

uniform vec3 object_color;
uniform vec3 light_color;

uniform vec3 light_position;
uniform vec3 diffuse_material;
uniform vec3 ambient_material;

out vec4 fragment_colour;


float amplify (float d, float scale, float offset) {
	d = scale * d + offset;
	d = clamp(d, 0, 1);
	d = 1 - exp2(-2 * d * d);
	return d;
}

void main () {
	vec3 norm = normalize(g_face_normal);
	float diff = abs(dot(norm, light_position));
	float ambient_strength = 0.8f;
	vec3 final = ambient_strength * ambient_material + diff * diffuse_material;

	float d1 = min(min(g_patch_distance.x, g_patch_distance.y), g_patch_distance.z);
	float d2 = min(min(g_tri_distance.x, g_tri_distance.y), g_tri_distance.z);
	final = amplify(d1, 50, -0.5) * amplify (d2, 60, -0.5) * object_color;
	fragment_colour = vec4(final, 1.0);

}
