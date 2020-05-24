/** \file VertexArrayGL.h
*/
#pragma once
#include "Renderer\VertexArray.h"
#include "glad\glad.h"
#include "GLFW\glfw3.h"


namespace Engine {
	/**
	\class VertexArrayGL
	GLFW implentation of a VAO
	*/
	class VertexArrayGL : public VertexArray {
	private:
		unsigned int m_RendererID;//!< Render ID
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;//!< vector containing Stored VBOS
		std::shared_ptr<IndexBuffer> m_IndexBuffer;//!< index Buffer
	public:
		//! Constructor
		VertexArrayGL();
		//! Destructor
		virtual ~VertexArrayGL() = default;

		//! Bind to GPU
		virtual void Bind() const override;
		//! Unbind from GPU
		virtual void Unbind() const override;

		//! Add VBO
		/*!
		\param buffer, VBO to Add
		*/
		virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer) override;
		//! Add Index Buffer
		/*!
		\param buffer, Index Buffer to Add
		*/
		virtual void addIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer) override;

		//! Get VBO
		/*!
		\param VBO used
		*/
		virtual std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffer() override { return m_VertexBuffers; }
		//! get Index Buffer
		/*!
		\param Index Buffer Used
		*/
		virtual const std::shared_ptr<IndexBuffer>& getIndexBuffer() const override { return m_IndexBuffer; }
	};

}