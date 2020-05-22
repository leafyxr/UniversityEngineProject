#include "engine_pch.h"
#include "GLFW\GLBuffer.h"
#include "glad\glad.h"
#include "GLFW\glfw3.h"

namespace Engine {

	//Vertex Buffer

	VertexBufferGL::VertexBufferGL(float * vertices, unsigned int size, BufferLayout layout)	//empty vertexbuffer, size HUGE
	{
		m_Layout = layout;
		glCreateBuffers(1, &m_rendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

		/*unsigned int index = 0;
		for (std::vector<BufferElement>::iterator it = layout.begin(); it != layout.end(); ++it)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				it->getCompoundCount(),
				ShaderDataType::shaderDataTypeToOpenGLType(it->getDataType()),
				it->isNormalized(),
				layout.getStride(),
				(const void*)it->getOffset());
			index++;
		}*/
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

	//Index Buffer

	IndexBufferGL::IndexBufferGL(unsigned int * indicies, unsigned int count) : m_Count(count)
	{
		glCreateBuffers(1, &m_rendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, indicies, GL_STATIC_DRAW);
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

}