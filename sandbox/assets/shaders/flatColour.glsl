#region Vertex

#version 440 core

layout(location = 0) in vec3 a_vertexPosition;
layout(location = 1) in vec3 a_vertexColour;

out vec3 fragmentColour;

uniform mat4 u_MVP;

void main()
{
	fragmentColour = a_vertexColour;
	gl_Position =  u_MVP * vec4(a_vertexPosition, 1.0f);
}

#region TessControl

#version 440 core

layout (vertices = 3) out;	//??? layout (vertices =1) out;

in vec3 fragmentColour[];

uniform vec3 u_viewPos;

out vec3 posTC[];

float alpha = 20.0f;
float lambda = 0.0105f / 5.0f;

float GetTessLevel(float dist1, float dist2)
{
	float tessLevel = 0.0f;
	float avgDist = (dist1 + dist2)/2.0f;

	float equation = -lambda * avgDist;

	tessLevel = exp(equation) * alpha;

	if (avgDist < 1.0f)
		return 1.0f;

	return tessLevel;
}

void main()
{
	int tessLevel = 1;
	float eyeToVertexDist0 = distance(u_viewPos, fragmentColour[0]);
	float eyeToVertexDist1 = distance(u_viewPos, fragmentColour[1]);
	float eyeToVertexDist2 = distance(u_viewPos, fragmentColour[2]);

	if (gl_InvocationID==0)
   {
		   // Calculate the tessellation levels
        gl_TessLevelOuter[0] = GetTessLevel(eyeToVertexDist1, eyeToVertexDist2); 
        gl_TessLevelOuter[1] = GetTessLevel(eyeToVertexDist2, eyeToVertexDist0); 
        gl_TessLevelOuter[2] = GetTessLevel(eyeToVertexDist0, eyeToVertexDist1);
        gl_TessLevelInner[0] = gl_TessLevelOuter[2]; 
   }

   posTC[gl_InvocationID] = fragmentColour[gl_InvocationID];
}

#region TessEvaluation

#version 440 core

layout(triangles, equal_spacing, ccw) in;

in vec3 posTC[];

out vec3 posES[];

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2)
{
   	return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;
}

vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2)
{
   	return vec3(gl_TessCoord.x) * v0 + vec3(gl_TessCoord.y) * v1 + vec3(gl_TessCoord.z) * v2;
}

void main()
{
	posES = interpolate3D(posTC[0], posTC[1], posTC[2]);
}

#region Geometry

#version 440 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec3 posES[];

out vec3 posG;
out vec3 GFragPos;

void main()
{
	for(int i = 0 ; i < 3; i++)
	{
		GFragPos = vec3(0.0);
		posG = posES[i];

		EmitVertex();
	}
EndPrimitive();
}

#region Fragment

#version 440 core

layout(location = 0) out vec4 colour;

in vec3 posG;
in vec3 GFragPos;

void main()
{
	colour = vec4(posG, 1.0);
}