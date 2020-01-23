#include "engine_pch.h"
#include "renderer/Buffer.h"
#include "Renderer\RenderAPI.h"
#include "GLFW\GLBuffer.h"

namespace Engine {
	VertexBuffer * VertexBuffer::Create(float * vertices, unsigned int size)
	{
		switch (RenderAPI::getApi()) {
		case RenderAPI::API::None: return nullptr;
		case RenderAPI::API::OpenGL: return new VertexBufferGL(vertices, size);
		}
		return nullptr;
	}
	IndexBuffer * IndexBuffer::Create(unsigned int * indicies, unsigned int size)
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