#include "engine_pch.h"
#include "renderer/Buffer.h"
#include "Renderer\RenderAPI.h"
#include "GLFW\GLBuffer.h"

namespace Engine {
	VertexBuffer * VertexBuffer::Create(void * vertices, unsigned int size, BufferLayout layout)
	{
		switch (RenderAPI::getApi()) {
		case RenderAPI::API::None: return nullptr;
		case RenderAPI::API::OpenGL: return new VertexBufferGL(vertices, size, layout);
		}
		return nullptr;
	}

	Engine::VertexBuffer* VertexBuffer::CreateEmpty(unsigned int size, BufferLayout layout)
	{
		switch (RenderAPI::getApi()) {
		case RenderAPI::API::None: return nullptr;
		case RenderAPI::API::OpenGL: return new VertexBufferGL(size, layout);
		}
		return nullptr;
	}

	IndexBuffer * IndexBuffer::Create(void * indicies, unsigned int size)
	{
		switch (RenderAPI::getApi()) {
		case RenderAPI::API::None: return nullptr;
		case RenderAPI::API::OpenGL: return new IndexBufferGL(indicies, size);
		}
		return nullptr;
	}
	void BufferLayout::addElement(BufferElement element)
	{
		m_Elements.push_back(element);
		calculateOffsetAndStride();
	}
}