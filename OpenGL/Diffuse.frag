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

struct Light
{
	vec3 position;
	vec3 color;
	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;
};

uniform Material material;
#define NR_LIGHTS 1
uniform Light light[NR_LIGHTS];

void main()
{
	vec4 finalColor = vec4(0);
	for(int i = 0; i < NR_LIGHTS; i++)
	{
		vec3 lightDir = normalize(light[i].position - retFragPos);
		float lambertianStrength = dot(lightDir, retNormal);
		vec3  ref1 = reflect(-lightDir, retNormal);
		float specularStrength = pow(max(dot(retViewDirection, ref1),0.0f),material.specularStrength);

		vec3 ambiant = texture(material.diffuseTexture, retTexCoord).rgb * light[i].ambientColor / NR_LIGHTS;
		vec3 lambertian = lambertianStrength * texture(material.diffuseTexture, retTexCoord).rgb * light[i].diffuseColor;
		vec3 specular  = specularStrength * texture(material.specularTexture, retTexCoord).rgb * light[i].specularColor;

		finalColor += vec4(ambiant + lambertian + specular, 1.0f);
	}
	FragColor = finalColor;
}