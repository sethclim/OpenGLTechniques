#version 330

in vec3 retNormal;
in vec2 retTexCoord;
in vec3 retFragPos;
in vec3 retViewDirection;

out vec4 FragColor;

struct Material
{
	float specularStrength;
	sampler2D diffuseTexture;
	sampler2D specularTexture;
};

uniform Material material;

void main()
{
	FragColor = vec4(texture(material.specularTexture, retTexCoord).rgb * abs(retFragPos),1.0f);
}