#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform bool is_hud_element;

// Output values to fragment shader
out vec3 world_position;
out vec3 world_normal;
out vec2 texcoord;

void main() {
	// compute world space vertex position and normal
	world_position = (Model * vec4(v_position, 1)).xyz;
	world_normal = normalize(mat3(Model) * v_normal);
	texcoord = v_texture_coord;

	if (is_hud_element)
		gl_Position = Model * vec4(v_position, 1.0);
	else
		gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}
