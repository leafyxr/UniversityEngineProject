/** \file GLMaterial.h
*/
#pragma once
#include "Renderer\Material.h"
#include <variant>

namespace Engine {

	/**
	\class GLMaterial
	GLFW implentation of a material
	*/
	class GLMaterial :public Material {
	private:
		std::shared_ptr<Shader> m_shader;//!< Pointer to Shader
		std::shared_ptr<VertexArray> m_geometry;//!< Pointer to VAO
		std::map<std::string, void*> m_data;//!< Map containing data to upload to shader
	public:
		//! Constructor
		/*!
		\param shader, shader to use
		\param VAO, Vertex Array Object
		*/
		GLMaterial(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& VAO);
		//! Initialise
		/*!
		\param shader, shader to use
		\param VAO, Vertex Array Object
		*/
		void init(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& VAO);
		//! Set Shader
		/*!
		\param shader, shader to set
		*/
		void setShader(const std::shared_ptr<Shader>& shader) override;
		//! Set Geometry
		/*!
		\param Geometry, VAO or VBO
		*/
		void setGeometry(const std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>>& geometry) override;
		//! set block of shader data
		/*!
		\param data, block of data
		*/
		void setDataBlock(const std::map<std::string, void *>& data) override;
		//! set data element to shader
		/*!
		\param dataName, name of data
		\param data, void pointer to data
		*/
		void setDataElement(const std::string& dataName, void * data) override;
		//void setVertexData(float * vertices, unsigned int size, unsigned int offset) override;

		//! get shader
		/*!
		\return shader used
		*/
		inline std::shared_ptr<Shader> getShader() override { return m_shader; }
		//! get geometry
		/*!
		\return VAO or VBO
		*/
		inline std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>> getGeometry() override { return std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>>(m_geometry); }
		//! get Data
		/*!
		\return block of last used shader data
		*/
		inline std::map<std::string, void*> getData() override { return m_data; }
	};

}