#include "engine_pch.h"
#include "GLFW\VertexArrayGL.h"

namespace Engine {

	static ShaderDataType GLSLStrToSDT(const std::string& glslSrc) {
		if (glslSrc == "bool")			return ShaderDataType::Bool;
		if (glslSrc == "int")			return ShaderDataType::Int;
		if (glslSrc == "ivec2")			return ShaderDataType::Int2;
		if (glslSrc == "ivec3")			return ShaderDataType::Int3;
		if (glslSrc == "ivec4")			return ShaderDataType::Int4;
		if (glslSrc == "float")			return ShaderDataType::Float;
		if (glslSrc == "vec2")			return ShaderDataType::Float2;
		if (glslSrc == "vec3")			return ShaderDataType::Float3;
		if (glslSrc == "vec4")			return ShaderDataType::Float4;
		if (glslSrc == "mat3")			return ShaderDataType::Mat3;
		if (glslSrc == "mat4")			return ShaderDataType::Mat4;
		if (glslSrc == "sampler2D")		return ShaderDataType::Sampler2D;
	}

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

	VertexArrayGL::VertexArrayGL()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	void VertexArrayGL::Bind() const
	{
		glBindVertexArray(m_RendererID);
		getVertexBuffer()->Bind();
		getIndexBuffer()->Bind();
	}

	void VertexArrayGL::Unbind() const
	{
		glBindVertexArray(0);
		getVertexBuffer()->Unbind();
		getIndexBuffer()->Unbind();
	}

	void VertexArrayGL::addVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer)
	{
		glBindVertexArray(m_RendererID);
		buffer->Bind();
		unsigned int index = 0;

		for (const BufferElement& element : buffer->getLayout()) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.getCompoundCount(), ShaderDataTypeToOpenGLType(element.Type), element.Normalised ? GL_TRUE : GL_FALSE,
				buffer->getLayout().getStride(), (const void*)element.Offset);
			index++;
		}
		//m_VertexBuffers.push_back(buffer);
	}

	void VertexArrayGL::addIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer)
	{
		glBindVertexArray(m_RendererID);
		buffer->Bind();
		m_IndexBuffer = buffer;
	}

}