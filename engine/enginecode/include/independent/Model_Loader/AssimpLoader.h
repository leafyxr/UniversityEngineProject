#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>

#include "systems/log.h"

namespace Engine {
	namespace Loader
	{
		class ASSIMPLoader
		{
		public:
			void ASSIMPLog(const std::string& filepath);
			const std::vector<float> getVertices() const { return m_assimpVertices; }
			const std::vector<unsigned int> getIndices() const { return m_assimpIndices; }

		private:
			std::vector<float> m_assimpVertices;
			std::vector<unsigned int> m_assimpIndices;
			void ASSIMPProcessMeshLog(aiMesh *mesh, const aiScene *scene);
			void ASSIMPProcessNodeLog(aiNode *node, const aiScene *scene);



		};
	}
}