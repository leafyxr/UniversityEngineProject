#region Vertex

#version 440 core

layout(location = 0) in vec3 a_vertexPosition;
layout(location = 1) in vec3 a_vertexNormal;
layout(location = 2) in vec2 a_texCoord;

out vec3 fragmentPos;
out vec3 normal;
out vec2 texCoord;

uniform mat4 u_model;
//uniform mat4 u_MVP;

void main()
{
	fragmentPos = (u_model * vec4(a_vertexPosition, 1.0f)).xyz;
	normal = mat3(transpose(inverse(u_model))) * a_vertexNormal;
	texCoord = vec2(a_texCoord.x, a_texCoord.y);
	//gl_Position =  u_tpmodel * vec4(a_vertexPosition, 1.0f);	//Move to tes
}

#region TessControl

#version 440 core

layout (vertices = 3) out;	//??? layout (vertices =1) out;

in vec3 normal[];
in vec3 fragmentPos[];
in vec2 texCoord[];

uniform vec3 u_viewPos;

out vec3 posTC[];
out vec2 tcTexCoords[];
//out vec3 viewPosTC[];
out vec3 normalTC[];

float alpha = 5.0f;
float lambda = 0.1f;

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
	//int tessLevel = 1;
	float eyeToVertexDist0 = distance(u_viewPos, fragmentPos[0]);
	float eyeToVertexDist1 = distance(u_viewPos, fragmentPos[1]);
	float eyeToVertexDist2 = distance(u_viewPos, fragmentPos[2]);

	if (gl_InvocationID==0)
   {
		//Calculate the tessellation levels
        gl_TessLevelOuter[0] = GetTessLevel(eyeToVertexDist1, eyeToVertexDist2); 
        gl_TessLevelOuter[1] = GetTessLevel(eyeToVertexDist2, eyeToVertexDist0); 
        gl_TessLevelOuter[2] = GetTessLevel(eyeToVertexDist0, eyeToVertexDist1);
        gl_TessLevelInner[0] = gl_TessLevelOuter[0];	//2
   }

   posTC[gl_InvocationID] = fragmentPos[gl_InvocationID];
   //viewPosTC[gl_InvocationID] = u_viewPos;
   tcTexCoords[gl_InvocationID] = texCoord[gl_InvocationID];
   normalTC[gl_InvocationID] = normal[gl_InvocationID];
}

#region TessEvaluation

#version 440 core

layout(triangles, equal_spacing, ccw) in;

in vec3 posTC[];
in vec2 tcTexCoords[];
//in vec3 viewPosTC[];
in vec3 normalTC[];

//uniform vec3 u_viewPos;
//uniform mat4 u_MVP;
uniform mat4 u_vp;

out vec3 posES;
out vec2 esTexCoords;
//out vec3 viewPosES;
out vec3 normalES;

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
	esTexCoords = interpolate2D(tcTexCoords[0], tcTexCoords[1], tcTexCoords[2]);
	//vec3 viewPosES = interpolate3D(u_viewPos[0], u_viewPos[1], u_viewPos[2]);
	normalES = interpolate3D(normalTC[0], normalTC[1], normalTC[2]);	//???
	gl_Position = u_vp * vec4(posES, 1.0f);
}

#region Geometry

#version 440 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec3 posES[];
in vec2 esTexCoords[];
//in vec3 viewPosES[];
in vec3 normalES[];

out vec3 posG;
out vec2 GTexCoords;
//out vec3 viewPosG;
out vec3 normalG;
out vec3 GFragPos;

vec3 getNormal()
{
    vec3 a = vec3(gl_in[1].gl_Position) - vec3(gl_in[0].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[0].gl_Position);
    return normalize(cross(a, b));
}

void main()
{
	for(int i = 0 ; i < 3; i++)
	{
		//GFragPos = vec3(0.0);
		gl_Position = gl_in[i].gl_Position;
		posG = posES[i];
		normalG = getNormal();	//???normalES[i] or getNormal()
		GTexCoords = esTexCoords[i];	//???
		//viewPosG = viewPosES[i];		//???

		EmitVertex();
	}
	EndPrimitive();

//	vec4 cen = (gl_in[0].gl_Position +  gl_in[1].gl_Position +  gl_in[2].gl_Position)/3 ;
//	//vec3 norm = getNormal() ;
//	for(int i = 0 ; i < 3; i++)
//	{
//		//gl_Position = cen ; //gl_in[i].gl_Position;
//		EmitVertex();
//		gl_Position = cen + vec4(norm*normLength,0.0);
//		EmitVertex();
//		EndPrimitive();
//	}
}

#region Fragment

#version 440 core

layout(location = 0) out vec4 colour;
layout(location = 1) out vec4 objectID;

in vec3 posG;
in vec2 GTexCoords;
//in vec3 viewPosG;
in vec3 normalG;

uniform vec3 u_lightPos; 
uniform vec3 u_viewPos; 
uniform vec3 u_lightColour;
uniform sampler2D u_texData;
uniform float u_objectID;

void main()
{
	float ambientStrength = 0.4f;
	vec3 ambient = ambientStrength * u_lightColour;
	
	vec3 norm = normalize(normalG);
	vec3 lightDir = normalize(u_lightPos - posG);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * u_lightColour;
	
	float specularStrength = 0.8f;
	vec3 viewDir = normalize(u_viewPos - posG);
	vec3 reflectDir = reflect(-lightDir, norm); 
	vec3 halfwayDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(norm, halfwayDir), 0.0f), 16.0f);
	vec3 specular = specularStrength * spec * u_lightColour;  
	
	colour = vec4((ambient + diffuse + specular), 1.0f) * texture(u_texData, GTexCoords);
	objectID = vec4(u_objectID, u_objectID, u_objectID, 1.0f);
}