#include "engine_pch.h"
#include "GLFW\GLMaterial.h"
#include "systems\log.h"

namespace Engine {
	GLMaterial::GLMaterial(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& VAO)
	{
		init(shader, VAO);
	}
	void GLMaterial::init(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& VAO)
	{
		m_shader = shader;
		m_geometry = VAO;
	}
	void GLMaterial::setShader(const std::shared_ptr<Shader>& shader)
	{
		m_shader = shader;
	}
	void GLMaterial::setGeometry(const std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>>& geometry)
	{
		m_geometry = std::get<std::shared_ptr<VertexArray>>(geometry);
	}
	void GLMaterial::setDataBlock(const std::map<std::string, void*>& data)
	{
		for (auto dataPair : data) {
			m_data[dataPair.first] = dataPair.second;
		}
	}
	void GLMaterial::setDataElement(const std::string & dataName, void * data)
	{
		m_data[dataName] = data;
	}
}