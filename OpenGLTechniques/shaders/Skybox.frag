#version 330

out vec4 FragColor;

in vec3 retTexCoords;

uniform samplerCube SkyboxTexture;

void main()
{
	FragColor = texture(SkyboxTexture, retTexCoords);
}