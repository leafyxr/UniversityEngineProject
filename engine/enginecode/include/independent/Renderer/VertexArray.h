/** \file VertexArray.h
*/
#pragma once
#include "Buffer.h"

namespace Engine {
	/**
	\class VertexArray
	Interface for VAO
	*/
	class VertexArray {
	public:
		//! Destructor
		virtual ~VertexArray() {};
		//! Bind to GPU
		virtual void Bind() const = 0;
		//! Unbind from GPU
		virtual void Unbind() const = 0;
		//! add VBO
		/*!
		\param VBO
		*/
		virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer) = 0;
		//! add index buffer
		/*!
		\param index buffer
		*/
		virtual void addIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer) = 0;

		//! get VBO
		/*!
		\return VBO
		*/
		virtual std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffer() = 0;
		//! get Index buffer
		/*!
		\return Index Buffer
		*/
		virtual const std::shared_ptr<IndexBuffer>& getIndexBuffer() const = 0;
		//! create array
		static VertexArray* Create();
	};

}