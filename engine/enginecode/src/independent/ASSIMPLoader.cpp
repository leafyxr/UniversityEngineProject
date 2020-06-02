#include "engine_pch.h"
#include "Model_Loader/AssimpLoader.h"

namespace Engine {

	void Loader::ASSIMPLoader::ASSIMPLog(const std::string& filepath)
	{
		Assimp::Importer importer;
		const aiScene *scene = importer.ReadFile(filepath, aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_Triangulate);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			NG_ERROR("Cannot load: {0}, ASSIMP Error {1}", filepath, importer.GetErrorString());
			return;
		}
		ASSIMPProcessNodeLog(scene->mRootNode, scene);
	}

	void Loader::ASSIMPLoader::ASSIMPProcessMeshLog(aiMesh *mesh, const aiScene *scene)
	{
		
		// Find vertex properties
		bool hasPositions = mesh->HasPositions();
		bool hasNormals = mesh->HasNormals();
		bool hasTangents = mesh->HasTangentsAndBitangents();
		unsigned int numColourChannels = mesh->GetNumColorChannels();
		unsigned int numUVChannels = mesh->GetNumUVChannels();

		NG_INFO("VERTICES");
		// Iterate through vertices
		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			// Get vertex data
			glm::vec3 position, normal, tangent, biTangent;
			std::vector<glm::vec4> colours(numColourChannels);
			std::vector<glm::vec2> texCoords(numUVChannels);

			if (hasPositions) position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
			if (hasNormals) normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
			if (hasTangents)
			{
				tangent = glm::vec3(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z);
				biTangent = glm::vec3(mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z);
			}

			for (unsigned int j = 0; j < numColourChannels; j++)
			{
				colours[j].r = mesh->mColors[j][i].r;
				colours[j].g = mesh->mColors[j][i].g;
				colours[j].b = mesh->mColors[j][i].b;
				colours[j].a = mesh->mColors[j][i].a;
			}

			for (unsigned int j = 0; j < numUVChannels; j++)
			{
				texCoords[j] = glm::vec2(mesh->mTextureCoords[j][i].x, mesh->mTextureCoords[j][i].y);
			}

			// Log part - assume position, normal and UV coords
			NG_INFO("P x:{0}, y:{1}, z:{2}, N x:{3}, y:{4}, z:{5}, T u:{6}, v{7}", position.x, position.y, position.z, normal.x, normal.y, normal.z, texCoords[0].x, texCoords[0].y);
			m_assimpVertices.push_back(position.x);
			m_assimpVertices.push_back(position.y);
			m_assimpVertices.push_back(position.z);
			m_assimpVertices.push_back(normal.x);
			m_assimpVertices.push_back(normal.y);
			m_assimpVertices.push_back(normal.z);
			m_assimpVertices.push_back(texCoords[0].x);
			m_assimpVertices.push_back(texCoords[0].y);
		}

		NG_INFO("INDICES");
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			// retrieve all indices of the face and store them in the indices vector
			for (unsigned int j = 0; j < face.mNumIndices; j++) unsigned int index = face.mIndices[j];

			// Log part - assume all faces are triangle and therefore have 3 indices
			NG_INFO("Face {0}: {1} {2} {3}", i, face.mIndices[0], face.mIndices[1], face.mIndices[2]);

			m_assimpIndices.push_back(face.mIndices[0]);
			m_assimpIndices.push_back(face.mIndices[1]);
			m_assimpIndices.push_back(face.mIndices[2]);
		}

		std::vector<aiTextureType> types = {
			aiTextureType_NONE,
			aiTextureType_DIFFUSE,
			aiTextureType_SPECULAR,
			aiTextureType_AMBIENT,
			aiTextureType_EMISSIVE,
			aiTextureType_HEIGHT,
			aiTextureType_NORMALS,
			aiTextureType_SHININESS,
			aiTextureType_OPACITY,
			aiTextureType_DISPLACEMENT,
			aiTextureType_LIGHTMAP,
			aiTextureType_REFLECTION,
			aiTextureType_BASE_COLOR,
			aiTextureType_NORMAL_CAMERA,
			aiTextureType_EMISSION_COLOR,
			aiTextureType_METALNESS,
			aiTextureType_DIFFUSE_ROUGHNESS,
			aiTextureType_AMBIENT_OCCLUSION,
			aiTextureType_UNKNOWN
		};


		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		for (auto type : types)
		{
			for (unsigned int i = 0; i < material->GetTextureCount(type); i++)
			{
				aiString str;
				material->GetTexture(type, i, &str);
				NG_INFO("Texture type:{0} filepath:{1}", type, str.C_Str());
			}

		}


		aiString stringValue;
		int intValue;
		float floatValue;
		aiColor3D colorValue;
		if (AI_SUCCESS == material->Get(AI_MATKEY_NAME, stringValue)) NG_INFO("Material name: {0}", stringValue.C_Str());

		if (AI_SUCCESS == material->Get(AI_MATKEY_SHADING_MODEL, intValue))
		{
			if (intValue == aiShadingMode_Flat) NG_INFO("Material shading model: Flat shading");
			if (intValue == aiShadingMode_Gouraud) NG_INFO("Material shading model: Gouraud");
			if (intValue == aiShadingMode_Phong) NG_INFO("Material shading model: Phong");
			if (intValue == aiShadingMode_Blinn) NG_INFO("Material shading model: Blinn");
			if (intValue == aiShadingMode_Toon)	NG_INFO("Material shading model: Toon");
			if (intValue == aiShadingMode_OrenNayar)NG_INFO("Material shading model: Oren Nayar");
			if (intValue == aiShadingMode_Minnaert)	NG_INFO("Material shading model: Minnaert");
			if (intValue == aiShadingMode_CookTorrance) NG_INFO("Material shading model: Cook Torrance");
			if (intValue == aiShadingMode_Fresnel)	NG_INFO("Material shading model: Fresnel");
			if (intValue == aiShadingMode_NoShading) NG_INFO("Material shading model: No shading");
		}

		if (AI_SUCCESS == material->Get(AI_MATKEY_ENABLE_WIREFRAME, intValue))
		{
			if (intValue == 0) NG_INFO("Material wireframe: false");
			else if (intValue == 1) NG_INFO("Material wireframe: true");
			else NG_INFO("Material wireframe: unknown");
		}


		if (AI_SUCCESS == material->Get(AI_MATKEY_SHININESS, floatValue)) NG_INFO("Material shininess: {0}", floatValue);
		if (AI_SUCCESS == material->Get(AI_MATKEY_SHININESS_STRENGTH, floatValue)) NG_INFO("Material shininess strength: {0}", floatValue);
		if (AI_SUCCESS == material->Get(AI_MATKEY_REFLECTIVITY, floatValue)) NG_INFO("Material reflectivity: {0}", floatValue);
		if (AI_SUCCESS == material->Get(AI_MATKEY_REFRACTI, floatValue)) NG_INFO("Material refraction index: {0}", floatValue);
		if (AI_SUCCESS == material->Get(AI_MATKEY_TRANSPARENCYFACTOR, floatValue)) NG_INFO("Material transprancy factor: {0}", floatValue);
		if (AI_SUCCESS == material->Get(AI_MATKEY_OPACITY, floatValue)) NG_INFO("Material opacity: {0}", floatValue);

		if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_AMBIENT, colorValue)) NG_INFO("Material ambient colour: {0}, {1}, {2}", colorValue.r, colorValue.g, colorValue.b);
		if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_DIFFUSE, colorValue)) NG_INFO("Material diffuse colour: {0}, {1}, {2}", colorValue.r, colorValue.g, colorValue.b);
		if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_SPECULAR, colorValue)) NG_INFO("Material specular colour: {0}, {1}, {2}", colorValue.r, colorValue.g, colorValue.b);
		if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_EMISSIVE, colorValue)) NG_INFO("Material emissive colour: {0}, {1}, {2}", colorValue.r, colorValue.g, colorValue.b);
		if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_REFLECTIVE, colorValue)) NG_INFO("Material reflective colour: {0}, {1}, {2}", colorValue.r, colorValue.g, colorValue.b);
		if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_TRANSPARENT, colorValue)) NG_INFO("Material tranparent colour: {0}, {1}, {2}", colorValue.r, colorValue.g, colorValue.b);

		/* Omitted material keys:
						AI_MATKEY_BLEND_FUNC
						AI_MATKEY_OPACITY
						AI_MATKEY_BUMPSCALING
						AI_MATKEY_GLOBAL_BACKGROUND_IMAGE
						AI_MATKEY_GLOBAL_SHADERLANG
						AI_MATKEY_SHADER_VERTEX
						AI_MATKEY_SHADER_FRAGMENT
						AI_MATKEY_SHADER_GEO
						AI_MATKEY_SHADER_TESSELATION
						AI_MATKEY_SHADER_PRIMITIVE
						AI_MATKEY_SHADER_COMPUTE
		*/

		
	}

	void Loader::ASSIMPLoader::ASSIMPProcessNodeLog(aiNode *node, const aiScene *scene)
	{
		std::string parentName = "Null";
		if (node->mParent != nullptr) parentName = node->mParent->mName.C_Str();
		if (node->mNumMeshes > 0) NG_INFO("MESHED NODE: {0} PARENT: {1}", node->mName.C_Str(), parentName);
		if (node->mNumMeshes == 0) NG_INFO("UNMESHED NODE: {0} PARENT: {1}", node->mName.C_Str(), parentName);

		aiMatrix4x4 *transform = &node->mTransformation;

		NG_INFO("TRANSFORM");
		NG_INFO("{0} {1} {2} {3}", transform->a1, transform->a2, transform->a3, transform->a4);
		NG_INFO("{0} {1} {2} {3}", transform->b1, transform->b2, transform->b3, transform->b4);
		NG_INFO("{0} {1} {2} {3}", transform->c1, transform->c2, transform->c3, transform->c4);
		NG_INFO("{0} {1} {2} {3}", transform->d1, transform->d2, transform->d3, transform->d4);

		

		// process all the node's meshes
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
			ASSIMPProcessMeshLog(mesh, scene);
		}

		//  Process child nodes
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			ASSIMPProcessNodeLog(node->mChildren[i], scene);
		}
		
	}

}