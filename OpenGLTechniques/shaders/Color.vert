#version 330

in vec3 vertices;
in vec3 normals;
in vec2 texCoords;

uniform mat4 WVP;

out vec3 retNormal;
out vec2 retTexCoord;

void main()
{
	gl_Position = WVP * vec4(vertices, 1.0f);
	retNormal = normalize(normals);
	retTexCoord = texCoords;
}