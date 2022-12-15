#version 330

in vec2 retTexCoord;
out vec4 FragColor;


uniform sampler2D ScreenTexture;

uniform vec2  resolution;
uniform float freq;
uniform float time;
uniform float amplitude;

uniform int blue;

void main()
{
	//New Fragment Position = Fragment Position + sine(Fragment X Position * Frequency + Time) * Amplitude
	vec2 texCoords = retTexCoord + sin(retTexCoord.x * freq + time) * amplitude;
	//ec2 texCoords =  newFragPos / resolution;

	vec4 color = texture(ScreenTexture, texCoords);

	if(blue == 1)
	{
		color.r /= 2;
		color.g /= 2;
	}

	FragColor = color;
}	 