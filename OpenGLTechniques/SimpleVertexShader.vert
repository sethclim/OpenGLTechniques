#version 330 // OpenGL version 2.1

in vec3 vertices; // value sent from application to this attribute
in vec4 colors;
in vec2 texCoords;

uniform mat4 WVP;

out vec4 retColor;
out vec2 retTexCoord;

void main()
{
	gl_Position = WVP * vec4(vertices, 1.0); // transform the model to screen projection; 
	retColor  = colors;
	retTexCoord = texCoords;
}