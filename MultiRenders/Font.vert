#version 330

in vec4 vertices;

uniform mat4 Projection;

out DATA
{
	vec2 texCoords;
} vs_out;

void main()
{
	gl_Position = Projection * vec4(vertices.xy, 0.0f, 1.0f);
	vs_out.texCoords = vertices.zw;
}