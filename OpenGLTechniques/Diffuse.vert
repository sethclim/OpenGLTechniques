#version 330

in vec3 vertices;
in vec3 normals;
in vec2 texCoords;
in vec3 tangents;
in vec3 bitangents;
layout (location = 10) in mat4 instanceMatrix;

uniform vec3 CameraPosition;
uniform mat4 World;
uniform mat4 WVP;
uniform bool EnableInstancing = false;

out vec3 retNormal;
out vec2 retTexCoord;
out vec3 retFragPos;
out vec3 retViewDirection;
out mat3 retTBN;

void main()
{
	mat4 world = World;
	if(EnableInstancing)
	{
		world *= instanceMatrix;
		gl_Position = WVP * instanceMatrix * vec4(vertices, 1.0);
	}
	else
	{
		gl_Position = WVP * vec4(vertices, 1.0);
	}
	retNormal = normalize(mat3(transpose(inverse(world))) * normals);
	retTexCoord = texCoords;
	retFragPos = vec3(world * vec4(vertices, 1.0f));
	retViewDirection = normalize(CameraPosition * retFragPos);

	vec3 T = normalize(vec3(world * vec4(tangents, 0.0f)));
	vec3 B = normalize(vec3(world * vec4(bitangents, 0.0f)));
	vec3 N = normalize(vec3(world * vec4(normals, 0.0f)));
	
	retTBN = mat3(T, B, N);
}