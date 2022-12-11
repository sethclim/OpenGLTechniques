#version 330

out vec4 FragColor;

in vec3 retTexCoords;

uniform samplerCube skyBoxTexture;

void main()
{
	FragColor = texture(skyBoxTexture, retTexCoords);
}