#version 330 core

layout (location = 0) out vec4 color;

uniform vec4 colour;
uniform vec2 light_pos;

in DATA
{
	vec4 position;
	vec2 uv;
	float tid;
	vec4 color;
} fs_in;

uniform sampler2D textures[32];

void main()
{
	// as the distance increases from light_pos, the length increases
	// causing intensity to become smaller
	float intensity = 200.0 / length(fs_in.position.xy - light_pos);
	//color = fs_in.color * intensity;		
	//color = fs_in.color;
	//color = texture(tex, fs_in.uv);
	//color = vec4(fs_in.uv.y,fs_in.uv.x,0,1);

	
	vec4 texColor = fs_in.color;
	if (fs_in.tid > 0.0)
	{
		int tid = int(fs_in.tid - 0.5);
		texColor = texture(textures[tid], fs_in.uv);
	}
	color = texColor;
}