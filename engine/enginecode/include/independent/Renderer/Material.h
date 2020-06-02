/** \file Material.h
*/
#pragma once
#include "Shader.h"
#include "Buffer.h"
#include "VertexArray.h"
#include <variant>

namespace Engine {
	/**
	\class Material
	Interface for Material
	*/
	class Material {
		
	public:
		//! Set Geometry
		/*!
		\param Geometry, VAO or VBO
		*/
		virtual void setShader(const std::shared_ptr<Shader>& shader) = 0;
		//! Set Geometry
		/*!
		\param Geometry, VAO or VBO
		*/
		virtual void setGeometry(const std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>>& geometry) = 0;
		//! set block of shader data
		/*!
		\param data, block of data
		*/
		virtual void setDataBlock(const std::map<std::string, void *>& data) = 0;
		//! set data element to shader
		/*!
		\param dataName, name of data
		\param data, void pointer to data
		*/
		virtual void setDataElement(const std::string& dataName, void * data) = 0;
		//virtual void setVertexData(float * vertices, unsigned int size, unsigned int offset) = 0;

		//! get shader
		/*!
		\return shader used
		*/
		virtual std::shared_ptr<Shader> getShader() = 0;
		//! get geometry
		/*!
		\return VAO or VBO
		*/
		virtual std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>> getGeometry() = 0;
		//! get Data
		/*!
		\return block of last used shader data
		*/
		virtual std::map<std::string, void*> getData() = 0;

		//! create with VAO
		/*!
		\param shader, shader to use
		\param VAO, Vertex Array Object
		*/
		static Material * create(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& VAO);
		//! create with VBO
		/*!
		\param shader, shader to use
		\param VBO, Vertex Array Object
		*/
		static Material * create(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexBuffer>& VBO);
	};

	
}