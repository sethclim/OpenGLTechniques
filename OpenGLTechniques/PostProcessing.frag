#version 330

in vec2 retTexCoord;
out vec4 FragColor;


uniform sampler2D ScreenTexture;

uniform vec2  resolution;
uniform float freq;
uniform float time;
uniform float amplitude;

uniform int blue;

//const float offset = 1.0 / 300.0;

void main()
{
	//New Fragment Position = Fragment Position + sine(Fragment X Position * Frequency + Time) * Amplitude
	vec2 newFragPos = gl_FragCoord.xy + sin(gl_FragCoord.x * freq + time) * amplitude;
	vec2 texCoords =  newFragPos / resolution;

	vec4 color;

	if(blue == 1)
	{
		vec4 tex = texture(ScreenTexture, texCoords);

		color = vec4(tex.r / 2, tex.g / 2, tex.b, 1.0);
	}
	else
	{
		color = texture(ScreenTexture, texCoords);
	}

	FragColor = color;
}	 