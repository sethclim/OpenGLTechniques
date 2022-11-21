#version 330

in vec4 retColor;
in vec2 retTexCoord;

out vec4 FragColor;
uniform sampler2D sampler1;
uniform sampler2D sampler2;

void main()
{
	FragColor = mix(texture(sampler1, retTexCoord), texture(sampler2, retTexCoord), .3);
}		