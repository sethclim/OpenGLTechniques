#version 330

in vec3 retNormal;
in vec2 retTexCoord;
in vec3 retFragPos;
in vec3 retViewDirection;
in mat3 retTBN;

out vec4 FragColor;

struct Material
{
	float     specularStrength;
	sampler2D diffuseTexture;
	sampler2D specularTexture;
	sampler2D normalTexture;
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
uniform bool EnableNormalMap = false;

void main()
{
	vec4 diffColor = texture(material.diffuseTexture, retTexCoord);
	if(diffColor.a == 0)
	{
		discard;
	}

	vec3 finalColor = vec3(0);
	for(int i = 0; i < NR_LIGHTS; i++)
	{
		vec3 lightDir = normalize(light[i].position - retFragPos);

		vec3 normal = retNormal;
		if(EnableNormalMap == true)
		{
			normal = texture(material.normalTexture, retTexCoord).rgb;
			normal = normal * 2.0f - 1.0f;
			normal = normalize(retTBN * normal);
		}

		float lambertianStrength = dot(lightDir, retNormal);
		vec3  ref1 = reflect(-lightDir, retNormal);
		float specularStrength = pow(max(dot(retViewDirection, ref1),0.0f),material.specularStrength);

		vec3 ambient = diffColor.rgb * light[i].ambientColor / NR_LIGHTS;
		vec3 lambertian = lambertianStrength * diffColor.rgb * light[i].diffuseColor;
		vec3 specular  = specularStrength * texture(material.specularTexture, retTexCoord).rgb * light[i].specularColor;

		finalColor += ambient + lambertian + specular;
	}

	FragColor = vec4(finalColor, diffColor.a);
}