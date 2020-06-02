#include "engine_pch.h"
#include "GLFW\GLBuffer.h"
#include "glad\glad.h"
#include "GLFW\glfw3.h"

namespace Engine {

	

	//Vertex Buffer

	VertexBufferGL::VertexBufferGL(void * vertices, unsigned int size, BufferLayout layout)
	{
		m_Layout = layout;
		glCreateBuffers(1, &m_rendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW);
	}

	VertexBufferGL::VertexBufferGL(unsigned int size, BufferLayout layout)
	{
		m_Layout = layout;
		glCreateBuffers(1, &m_rendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
		glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_DYNAMIC_DRAW);
	}

	VertexBufferGL::~VertexBufferGL()
	{
		glDeleteBuffers(1, &m_rendererID);
	}
	void VertexBufferGL::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
	}
	void VertexBufferGL::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexBufferGL::Edit(float * vertices, unsigned int size, unsigned int offset)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
		glBufferSubData(GL_ARRAY_BUFFER, offset, size, vertices);
	}

	//Index Buffer

	IndexBufferGL::IndexBufferGL(void * indicies, unsigned int count) : m_Count(count)
	{
		glCreateBuffers(1, &m_rendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indicies, GL_DYNAMIC_DRAW);
	}
	IndexBufferGL::~IndexBufferGL()
	{
		glDeleteBuffers(1, &m_rendererID);
	}
	void IndexBufferGL::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
	}
	void IndexBufferGL::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void IndexBufferGL::Edit(unsigned int * indicies, unsigned int size, unsigned int offset)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, indicies);
	}

}