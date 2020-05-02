#region Vertex

#version 440 core

layout(location = 0) in vec3 a_vertexPosition;
layout(location = 1) in vec3 a_vertexNormal;
layout(location = 2) in vec2 a_texCoord;

out vec3 fragmentPos;
out vec3 normal;
out vec2 texCoord;

uniform mat4 u_model;
uniform mat4 u_MVP;

void main()
{
	fragmentPos = vec3(u_model * vec4(a_vertexPosition, 1.0));
	normal = mat3(transpose(inverse(u_model))) * a_vertexNormal;
	texCoord = vec2(a_texCoord.x, a_texCoord.y);
	gl_Position =  u_MVP * vec4(a_vertexPosition,1.0);
}

#region Tessalation

#version 440 core

layout (vertices = 3) out;

in vec3 normal[];
in vec3 fragmentPos[];
in vec2 texCoord[];

uniform vec3 u_viewPos;

out vec3 posTC[];
out vec2 tcTexCoords[];
out vec3 viewPosTC[];
out vec3 normalTC[];

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
	int tessLevel = 1;
	float eyeToVertexDist0 = distance(u_viewPos, fragmentPos[0]);
	float eyeToVertexDist1 = distance(u_viewPos, fragmentPos[1]);
	float eyeToVertexDist2 = distance(u_viewPos, fragmentPos[2]);

	if (gl_InvocationID==0)
   {
		   // Calculate the tessellation levels
        gl_TessLevelOuter[0] = GetTessLevel(eyeToVertexDist1, eyeToVertexDist2); 
        gl_TessLevelOuter[1] = GetTessLevel(eyeToVertexDist2, eyeToVertexDist0); 
        gl_TessLevelOuter[2] = GetTessLevel(eyeToVertexDist0, eyeToVertexDist1);
        gl_TessLevelInner[0] = gl_TessLevelOuter[2]; 
   }

   posTC[gl_InvocationID] = fragmentPos[gl_InvocationID];
   viewPosTC[gl_InvocationID] = u_viewPos;
   tcTexCoords[gl_InvocationID] = texCoord[gl_InvocationID];
   normalTC[gl_InvocationID] = normal;
}

#region Fragment

#version 440 core

layout(location = 0) out vec4 colour;

in vec3 normal;
in vec3 fragmentPos;
in vec2 texCoord;

in vec3 posTC[];
in vec2 tcTexCoords[];
in vec3 viewPosTC[];
in vec3 normalTC[];

uniform vec3 u_lightPos; 
uniform vec3 u_viewPos; 
uniform vec3 u_lightColour;
uniform sampler2D u_texData;

void main()
{
	float ambientStrength = 0.4;
	vec3 ambient = ambientStrength * u_lightColour;
	
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(u_lightPos - fragmentPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * u_lightColour;
	
	float specularStrength = 0.8;
	vec3 viewDir = normalize(u_viewPos - fragmentPos);
	vec3 reflectDir = reflect(-lightDir, norm); 
	vec3 halfwayDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(norm, halfwayDir), 0.0), 16);
	vec3 specular = specularStrength * spec * u_lightColour;  
	
	colour = vec4((ambient + diffuse + specular), 1.0) * texture(u_texData, texCoord);
}