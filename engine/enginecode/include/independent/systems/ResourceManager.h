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
		std::shared_ptr<G> & get(const std::string& key); //!< Get a point to an asset. Return nullptr if not found
	private:
		std::map<std::string, std::shared_ptr<G>> m_container; //Data structure to hold assets
	};

	template <class G>
	bool AssetManager<G>::contains(const std::string& key)
	{
		if (m_container.find(key) != m_container.end())
			return true;

		return false;
	}

	template <class G>
	std::shared_ptr<G> & AssetManager<G>::get(const std::string& key)
	{
		if (contains(key))
			return m_container.at(key);
		/*else
			return nullptr;*/
	}

	template <class G>
	void AssetManager<G>::add(const std::string& key, std::shared_ptr<G>& element)
	{
		if (contains(key))
		{
			NG_WARN("'{0}' is already in the container ", key);
		}
		else
		{
			m_container[key] = element;
		}
	}

	class ResourceManager : public System
	{
	private:
		AssetManager<Shader> m_shaders;
		AssetManager<IndexBuffer> m_indexBuffers;
		AssetManager<VertexBuffer> m_vertexBuffers;
		AssetManager<VertexArray> m_vertexArrays;
		AssetManager<Material> m_materials;
		AssetManager<Texture> m_textures;

	public:
		void start(SystemSignal init, ...) {}; //!< Start the system
		void stop(SystemSignal close, ...) {}; //!< Stop the system - change this to free all resources


		std::shared_ptr<Shader> addShader(const std::string& name, const std::string& filepath);
		std::shared_ptr<IndexBuffer> addIndexBuffer(const std::string& name, unsigned int* indices, unsigned int count);
		std::shared_ptr<VertexBuffer> addVertexBuffer(const std::string& name, float* vertices, unsigned int size, BufferLayout& layout);
		std::shared_ptr<VertexArray> addVertexArray(const std::string& name);
		std::shared_ptr<Material> addMaterial(const std::string& name, const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);
		std::shared_ptr<Texture> addTexture(const std::string& name, const std::string& filepath);
		std::shared_ptr<Texture> addTexture(const std::string& name, unsigned int width, unsigned int height, unsigned int channels, unsigned char* textureData);


		inline AssetManager<Shader>& getShaderType() { return m_shaders; }
		inline AssetManager<IndexBuffer>& getIndexBufferType() { return m_indexBuffers; }
		inline AssetManager<VertexBuffer>& getVertexBufferType() { return m_vertexBuffers; }
		inline AssetManager<VertexArray>& getVertexArrayType() { return m_vertexArrays; }
		inline AssetManager<Material>& getMaterialType() { return m_materials; }
		inline AssetManager<Texture>& getTextureType() { return m_textures; }

	};
}
