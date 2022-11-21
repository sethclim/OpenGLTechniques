#version 330

in vec3 vertices;
in vec3 normals;
in vec2 texCoords;

uniform vec3 CameraPosition;
uniform mat4 World;
uniform mat4 WVP;

out vec3 retNormal;
out vec2 retTexCoord;
out vec3 retFragPos;
out vec3 retViewDirection;

void main()
{
	gl_Position = WVP * vec4(vertices, 1.0);
	retNormal = normalize(mat3(transpose(inverse(World))) * normals);
	retTexCoord = texCoords;
	retFragPos = vec3(World * vec4(vertices, 1.0f));
	retViewDirection = normalize(CameraPosition * retFragPos);
}