#version 330

in vec2 retTexCoord;
out vec4 FragColor;


uniform sampler2D ScreenTexture;

uniform vec2  resolution;
uniform float freq;
uniform float time;
uniform float amplitude;

//const float offset = 1.0 / 300.0;



void main()
{
//	vec2 offsets[9] = vec2[](
//		vec2(-offset, offset),
//		vec2(0.0f,offset),
//		vec2(offset, offset),
//		vec2(-offset, 0.0f),
//		vec2(0.0f,0.0f),
//		vec2(offset, 0.0f),
//		vec2(-offset, -offset),
//		vec2(0.0f, -offset),
//		vec2(offset, -offset)
//	);
//
//
//	float kernel[9] = float[](
//		1, 1, 1,
//		1, -8, 1,
//		1, 1, 1
//	);
//
//	vec3 sampleTex[9];
//
//	for(int i = 0; i < 9; i++)
//	{
//		sampleTex[i] = vec3(texture(ScreenTexture, retTexCoord.st + offsets[i]));
//	}

//	vec3 col = vec3(0.0);
//	for(int i = 0; i < 9; i++)
//	 col += sampleTex[i] * kernel[i];

	//vec2 uv = gl_FragCoord.xy; // retTexCoord.st;

	//New Fragment Position = Fragment Position + sine(Fragment X Position * Frequency + Time) * Amplitude
	vec2 newFragPos = gl_FragCoord.xy + sin(gl_FragCoord.x * freq + time) * amplitude;
	vec2 texCoords =  newFragPos / resolution;

	vec4 color = texture(ScreenTexture, texCoords);

	FragColor = color;
}	 