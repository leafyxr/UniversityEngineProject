#region Vertex
#version 440 core

layout(location = 0) in vec4 vertex;

out vec2 texCoord;

uniform mat4 u_projection;

void main() 
{
	texCoord = vertex.zw;
	gl_Position = u_projection *  vec4(vertex.xy, 0.0, 1.0);
}

#region Fragment

#version 440 core

layout (location = 0) out vec4 colour;

in vec2 texCoord;

uniform sampler2D u_texData;
uniform vec3 u_fontColour;

void main()
{
	colour = vec4(1.0, 1.0, 1.0,texture(u_texData, texCoord).r);
	colour *=  vec4(u_fontColour, 1.0);
}