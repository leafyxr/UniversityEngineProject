/** \file resourceManager.cpp
*/
#include "engine_pch.h"

#include "systems/ResourceManager.h"

namespace Engine
{
	/*AssetManager<Texture> ResourceManager::m_textures;
	AssetManager<IndexBuffer> ResourceManager::m_indexBuffers;
	AssetManager<VertexBuffer> ResourceManager::m_vertexBuffers;
	AssetManager<VertexArray> ResourceManager::m_vertexArrays;
	AssetManager<Material> ResourceManager::m_materials;
	AssetManager<Shader> ResourceManager::m_shaders;*/

	//AssetManager<Texture> ResourceManager::getIndexBufferType;
	//AssetManager<IndexBuffer> ResourceManager::m_indexBuffers;
	//AssetManager<VertexBuffer> ResourceManager::m_vertexBuffers;
	//AssetManager<VertexArray> ResourceManager::m_vertexArrays;
	//AssetManager<Material> ResourceManager::m_materials;
	//AssetManager<Shader> ResourceManager::m_shaders;

	

	std::shared_ptr<Shader> ResourceManager::addShader(const std::string & name, const std::string& filepath)
	{
		std::shared_ptr<Shader> m_shader;
		m_shader.reset(Shader::create(filepath));
		m_shaders.add(name, m_shader);
		return m_shader;
	}

	std::shared_ptr<IndexBuffer> ResourceManager::addIndexBuffer(const std::string & name, unsigned int * indices, unsigned int count)
	{
		std::shared_ptr<IndexBuffer> m_indexBuffer;
		m_indexBuffer.reset(IndexBuffer::Create(indices, count));
		m_indexBuffers.add(name, m_indexBuffer);
		return m_indexBuffer;
	}

	std::shared_ptr<VertexBuffer> ResourceManager::addVertexBuffer(const std::string & name, void * vertices, unsigned int size, BufferLayout& layout)
	{
		std::shared_ptr<VertexBuffer> m_vertexBuffer;
		m_vertexBuffer.reset(VertexBuffer::Create(vertices, size, layout));
		m_vertexBuffers.add(name, m_vertexBuffer); 
		return m_vertexBuffer;
	}

	std::shared_ptr<VertexArray> ResourceManager::addVertexArray(const std::string & name)
	{
		std::shared_ptr<VertexArray> m_vertexArray;
		m_vertexArray.reset(VertexArray::Create());
		m_vertexArrays.add(name, m_vertexArray);
		return m_vertexArray;
	}

	std::shared_ptr<Material> ResourceManager::addMaterial(const std::string & name, const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{

		std::shared_ptr<Material> m_material;
		m_material.reset(Material::create(shader,vertexArray));
		m_materials.add(name, m_material);
		return m_material;
	}

	std::shared_ptr<Texture> ResourceManager::addTexture(const std::string & name, const std::string& filepath)
	{
		std::shared_ptr<Texture> m_texture;
		m_texture.reset(Texture::createFromFile(filepath));
		m_textures.add(name, m_texture);
		return m_texture;
	}

	std::shared_ptr<Texture> ResourceManager::addTexture(const std::string & name, unsigned int width, unsigned int height, unsigned int channels, unsigned char * textureData)
	{
		std::shared_ptr<Texture> m_texture;
		m_texture.reset(Texture::createFromRawData(width, height, channels, textureData));
		m_textures.add(name,m_texture);
		return m_texture;
	}
}