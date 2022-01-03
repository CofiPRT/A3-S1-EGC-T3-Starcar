#version 330

#define MAX_LIGHTS (40)

#define CONSTANT_ATTENUATION_FACTOR (1.f)
#define LINEAR_ATTENUATION_FACTOR	(0.25f)
#define SQUARED_ATTENUATION_FACTOR	(0.125f)

uniform sampler2D texture_1;

// get color value from vertex shader
in vec3 world_position;
in vec3 world_normal;
in vec2 texcoord;

// Uniforms for light properties
uniform vec3 light_directions[MAX_LIGHTS];
uniform vec3 light_positions[MAX_LIGHTS];
uniform vec3 light_colors[MAX_LIGHTS];
uniform bool light_types[MAX_LIGHTS];
uniform float light_cutoffs[MAX_LIGHTS];
uniform float light_intensities[MAX_LIGHTS];

uniform int light_source_count;

uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform bool is_hud_element;

layout(location = 0) out vec4 out_color;

float get_att(float dist) {
	return 1.f / (CONSTANT_ATTENUATION_FACTOR +
		LINEAR_ATTENUATION_FACTOR * dist +
		SQUARED_ATTENUATION_FACTOR * dist * dist);
}

vec4 non_hud_color() {
	// acquire vectors
	vec3 N = normalize(world_normal);
	vec3 V = normalize(eye_position - world_position);

	vec3 total_light_color = vec3(0);

	for (int i = 0; i < light_source_count; i++) {
		vec3 L = normalize(light_positions[i] - world_position);
		vec3 R = normalize(reflect(L, world_normal));
		vec3 H = normalize(L + V);

		// compute diffuse light component
		float diffuse_light = material_kd * max(0, dot(normalize(N), L));

		// compute specular light component
		float specular_light = diffuse_light > 0 ? material_ks * pow(max(0, dot(N, H)), material_shininess) : 0;

		// compute light
		float light = 0;

		if (!light_types[i]) {
			// normal light type
			float dist = distance(light_positions[i], world_position);
			float att = get_att(dist * 1.f / light_intensities[i]);

			light = att * (diffuse_light + specular_light);
		} else {
			// spot light type
			float spot_light_max = cos(light_cutoffs[i]);
			float spot_light_curr = dot(-L, light_directions[i]);

			if (spot_light_curr < spot_light_max) {
				// don't override the light from other objects
				light = 0;
			} else {
				// use quadratic attenuation
				float spot_light_rel_diff = (spot_light_curr - spot_light_max) / (1 - spot_light_max);
				float att_spot = spot_light_rel_diff * spot_light_rel_diff;

				float dist = distance(light_positions[i], world_position);
				float att_dist = get_att(dist * 1.f / light_intensities[i]);

				float att = att_spot * att_dist;
			
				light = att * (diffuse_light + specular_light);
			}
		}

		total_light_color += light * light_colors[i];
	}

	// define ambient light component
	float ambient_light = 0.25;

	vec3 texture_color = vec3(texture2D(texture_1, texcoord));
	
	// write pixel out color
	return vec4(texture_color * ambient_light + total_light_color, 1);
}

vec4 hud_color() {
	vec3 texture_color = vec3(texture2D(texture_1, texcoord));

	// write pixel out color
	return vec4(texture_color, 1);
}

void main() {
	if (!is_hud_element)
		out_color = non_hud_color();
	else
		out_color = hud_color();
}