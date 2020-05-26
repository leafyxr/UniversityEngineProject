/** \file GLBuffer.h
*/
#pragma once
#include "Renderer\Buffer.h"
#include "glad\glad.h"
#include "GLFW\glfw3.h"

namespace Engine {

	//! Shader Data Type to OpenGL Type
	/*!
	\param type, shader data type
	\return OpenGL type
	*/
	static GLenum ShaderDataTypeToOpenGLType(ShaderDataType type) {
		switch (type) {
		case ShaderDataType::Int:			return GL_INT;
		case ShaderDataType::Int2:			return GL_INT;
		case ShaderDataType::Int3:			return GL_INT;
		case ShaderDataType::Int4:			return GL_INT;
		case ShaderDataType::Float:			return GL_FLOAT;
		case ShaderDataType::Float2:		return GL_FLOAT;
		case ShaderDataType::Float3:		return GL_FLOAT;
		case ShaderDataType::Float4:		return GL_FLOAT;
		case ShaderDataType::Mat3:			return GL_FLOAT;
		case ShaderDataType::Mat4:			return GL_FLOAT;
		case ShaderDataType::Bool:			return GL_BOOL;
		}
		return 0;
	}

	/**
	\class VertexBufferGL
	GLFW implentation of a VBO
	*/
	class VertexBufferGL : public VertexBuffer {
	public:
		//! Constructor
		/*!
		\param vertices
		\param size
		*/
		VertexBufferGL(float* vertices, unsigned int size, BufferLayout layout);

		VertexBufferGL(unsigned int size, BufferLayout layout);
		//! Destructor
		virtual ~VertexBufferGL();

		//! Bind to GPU
		virtual void Bind() const override;
		//! Unbind from GPU
		virtual void Unbind() const override;

		virtual void Edit(float* vertices, unsigned int size, unsigned int offset) override;
		
		//! Get buffer layout
		/*!
		\return buffer layout
		*/
		virtual const BufferLayout& getLayout() const override { return m_Layout;  }
		//! set layout
		/*!
		\param layout, buffer layout
		*/
		virtual void setLayout(const BufferLayout& layout) override { m_Layout = layout; }
	private:
		bool m_Dynamic;
		unsigned int m_rendererID;//!< Render ID
		BufferLayout m_Layout;//!< Buffer Layout
	};

	/**
	\class IndexBufferGL
	GLFW implentation of a Index Buffer
	*/
	class IndexBufferGL : public IndexBuffer {
	public:
		//! Constructor
		/*!
		\param indicies
		\param count
		*/
		IndexBufferGL(unsigned int * indicies, unsigned int count);

		IndexBufferGL(unsigned int count);

		//! Destructor
		virtual ~IndexBufferGL();

		//! Bind to GPU
		virtual void Bind() const override;
		//! Unbind from GPU
		virtual void Unbind() const override;

		virtual void Edit(unsigned int* indicies, unsigned int size, unsigned int offset) override;

		//! get count
		/*!
		\return count
		*/
		virtual unsigned int getCount() const { return m_Count; }
		//! Get buffer layout
		/*!
		\return buffer layout
		*/
		virtual const BufferLayout& getLayout() const override { return m_Layout; }
		//! set layout
		/*!
		\param layout, buffer layout
		*/
		virtual void setLayout(const BufferLayout& layout) override { m_Layout = layout; }
	private:
		bool m_Dynamic;
		unsigned int m_rendererID;//!< Render ID
		unsigned int m_Count;//!< Size of Buffer
		BufferLayout m_Layout;//!< Buffer Layout

	};

}