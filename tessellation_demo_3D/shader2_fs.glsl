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
