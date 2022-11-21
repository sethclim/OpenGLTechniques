#version 330

in DATA
{
	vec2 texCoords;
} fs_in;

struct Material
{
	sampler2D diffuseTexture;
};

uniform Material material;
uniform vec3 TextColor;

out vec4 FragColor;

void main()
{
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(material.diffuseTexture, fs_in.texCoords).r);
	FragColor = vec4(TextColor, 1.0) * sampled;
}
