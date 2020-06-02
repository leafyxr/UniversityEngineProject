#region Vertex
#version 440 core

layout(location = 0) in vec3 a_vertexPos;
layout(location = 1) in vec2 a_texCoord;
layout(location = 2) in int a_texIndex;

out vec3 fragmentPos;
out vec3 normal;
out vec2 texCoord;
out int texIndex;

uniform mat4 u_viewProjection;
uniform mat4 u_model;

void main() 
{
	texCoord = vec2(a_texCoord.x, a_texCoord.y);
	texIndex = a_texIndex;
	gl_Position = u_viewProjection * u_model * vec4(a_vertexPos, 1.0f);
}

#region Fragment

#version 440 core

layout (location = 0) out vec4 colour;

in vec2 texCoord;
in int texIndex;

uniform sampler2D u_texData;


void main()
{
	colour = texture(u_texData, texCoord);
}