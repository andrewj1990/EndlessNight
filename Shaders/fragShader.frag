#version 330 core

layout (location = 0) out vec4 color;

uniform vec4 colour;
uniform vec2 light_pos;

in DATA
{
	vec4 position;
	vec2 uv;
	vec4 color;
} fs_in;

uniform sampler2D tex;

void main()
{
	// as the distance increases from light_pos, the length increases
	// causing intensity to become smaller
	float intensity = 200.0 / length(fs_in.position.xy - light_pos);
	//color = fs_in.color * intensity;		
	//color = fs_in.color;
	color = texture(tex, fs_in.uv);
	//color = vec4(fs_in.uv.y,0,0,1);
}