/** \file application.h
*/
#pragma once

#include "system.h"
#include "log.h"

#include "Renderer/Shader.h"
#include "renderer/renderAPI.h"
#include "renderer/shader.h"
#include "renderer/texture.h"
#include "renderer/renderer.h"

#include <string>
#include <map>

namespace Engine
{
	template <class G>
	class AssetManager
	{
	public:
		bool contains(const std::string& key); //!< Is this item in the container already?
		void add(const std::string& key, std::shared_ptr<G>& element); //!< Add element to the container
		std::shared_ptr<G> get(const std::string& key); //!< Get a point to an asset. Return nullptr if not found
	private:
		std::map<std::string, std::shared_ptr<G>> m_container; //Data structure to hold assets
	};

	class ResourceManager : public System
	{
	private:
		static AssetManager<Shader> m_shaders;
		static AssetManager<IndexBuffer> m_indexBuffers;
		static AssetManager<VertexBuffer> m_vertexBuffers;
		static AssetManager<VertexArray> m_vertexArrays;
		static AssetManager<Material> m_materials;
		static AssetManager<Texture> m_textures;

	public:
		void start(SystemSignal init, ...) {}; //!< Start the system
		void stop(SystemSignal close, ...) {}; //!< Stop the system - change this to free all resources


		//static add functions
		static std::shared_ptr<Shader> addShader(const std::string& name, const std::string& filepath);
		static std::shared_ptr<IndexBuffer> addIndexBuffer(const std::string& name, unsigned int* indices, unsigned int count);
		static std::shared_ptr<VertexBuffer> addVertexBuffer(const std::string& name, float* vertices, unsigned int size, BufferLayout& layout);
		static std::shared_ptr<VertexArray> addVertexArray(const std::string& name);
		static std::shared_ptr<Material> addMaterial(const std::string& name, const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);
		static std::shared_ptr<Texture> addTexture(const std::string& name, const std::string& filepath);
		static std::shared_ptr<Texture> addTexture(const std::string& name, unsigned int width, unsigned int height, unsigned int channels, unsigned char* textureData);


		inline std::shared_ptr<Shader> getShaderType(const std::string& name) const { return m_shaders.get(name); }
		inline std::shared_ptr<IndexBuffer> getIndexBufferType(const std::string& name) const { return m_indexBuffers.get(name); }
		inline std::shared_ptr<VertexBuffer> getVertexBufferType(const std::string& name) const { return m_vertexBuffers.get(name); }
		inline std::shared_ptr<VertexArray> getVertexArrayType(const std::string& name) const { return m_vertexArrays.get(name); }
		inline std::shared_ptr<Material> getMaterialType(const std::string& name) const { return m_materials.get(name); }
		inline std::shared_ptr<Texture> getTextureType(const std::string& name) const { return m_textures.get(name); }

	};
}
