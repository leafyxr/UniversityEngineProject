/** \file resourceManager.cpp
*/
#include "engine_pch.h"

#include "systems/ResourceManager.h"

namespace Engine
{
	AssetManager<Texture> ResourceManager::m_textures;
	AssetManager<IndexBuffer> ResourceManager::m_indexBuffers;
	AssetManager<VertexBuffer> ResourceManager::m_vertexBuffers;
	AssetManager<VertexArray> ResourceManager::m_vertexArrays;
	AssetManager<Material> ResourceManager::m_materials;
	AssetManager<Shader> ResourceManager::m_shaders;

	template <class G>
	bool AssetManager<G>::contains(const std::string& key)
	{
		auto it = m_container.begin();
		while (it != m_container.end())
		{
			if (it->first == key)
				return true;
			it++;
		}
		return false;
	}

	template <class G>
	std::shared_ptr<G> AssetManager<G>::get(const std::string& key)
	{
		if (contains(key))
			return std::shared_ptr<G>(m_container.at(key));
		else
			return nullptr;
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
			m_container.insert(std::pair<std::string, std::shared_ptr<G>>(key, element));
		}
	}


	std::shared_ptr<Shader> ResourceManager::addShader(const std::string & name, const std::string& filepath)
	{
		std::shared_ptr<Shader> m_shader;
		m_shaders.add(name, std::shared_ptr<Shader>(Shader::create(filepath)));
		m_shader = m_shaders.get(name);
		return std::shared_ptr<Shader>(m_shaders.get(filepath));
	}

	std::shared_ptr<IndexBuffer> ResourceManager::addIndexBuffer(const std::string & name, unsigned int * indices, unsigned int count)
	{
		std::shared_ptr<IndexBuffer> m_indexBuffer;
		m_indexBuffers.add(name, std::shared_ptr<IndexBuffer>(IndexBuffer::Create(indices, count)));
		m_indexBuffer = m_indexBuffers.get(name);
		return std::shared_ptr<IndexBuffer>(m_indexBuffers.get(name));
	}

	std::shared_ptr<VertexBuffer> ResourceManager::addVertexBuffer(const std::string & name, float * vertices, unsigned int size, BufferLayout& layout)
	{
		std::shared_ptr<VertexBuffer> m_vertexBuffer;
		m_vertexBuffers.add(name, std::shared_ptr<VertexBuffer>(VertexBuffer::Create(vertices, size, layout)));
		m_vertexBuffer = m_vertexBuffers.get(name);
		return std::shared_ptr<VertexBuffer>(m_vertexBuffers.get(name));
	}

	std::shared_ptr<VertexArray> ResourceManager::addVertexArray(const std::string & name)
	{
		std::shared_ptr<VertexArray> m_vertexArray;
		m_vertexArrays.add(name, std::shared_ptr<VertexArray>(VertexArray::Create()));
		m_vertexArray = m_vertexArrays.get(name);
		return std::shared_ptr<VertexArray>(m_vertexArrays.get(name));
	}

	std::shared_ptr<Material> ResourceManager::addMaterial(const std::string & name, const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		std::shared_ptr<Material> m_material;
		m_materials.add(name, std::shared_ptr<Material>(Material::create(shader, vertexArray)));
		m_material = m_materials.get(name);
		return std::shared_ptr<Material>(m_materials.get(name));
	}

	std::shared_ptr<Texture> ResourceManager::addTexture(const std::string & name, const std::string& filepath)
	{
		std::shared_ptr<Texture> m_texture;
		m_textures.add(name, std::shared_ptr<Texture>(Texture::createFromFile(filepath)));
		m_texture = m_textures.get(name);
		return std::shared_ptr<Texture>(m_textures.get(filepath));
	}

	std::shared_ptr<Texture> ResourceManager::addTexture(const std::string & name, unsigned int width, unsigned int height, unsigned int channels, unsigned char * textureData)
	{
		std::shared_ptr<Texture> m_texture;
		m_textures.add(name, std::shared_ptr<Texture>(Texture::createFromRawData(width, height, channels, textureData)));
		m_texture = m_textures.get(name);
		return std::shared_ptr<Texture>(m_textures.get(name));
	}
}