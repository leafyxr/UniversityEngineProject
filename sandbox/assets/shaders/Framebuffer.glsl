#region Vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

void main()
{
	TexCoords = aTexCoords;
	gl_Position = vec4(aPos, 1.0);
}

#region Fragment

#version 330 core
in vec2 TexCoords;
in vec3 fragPosCS;

uniform sampler2D u_texData;
out vec4 fragColor;

void main()
{
	fragColor = texture2D(u_texData, TexCoords);
}