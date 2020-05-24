/** \file Buffer.h
*/
#pragma once
#include "engine_pch.h"


namespace Engine {

	/**
	\class Shader Data Type
	*/
	enum class ShaderDataType {
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool, Sampler2D
	};

	static unsigned int ShaderDataTypeSize(ShaderDataType type) {
		switch (type) {
		case ShaderDataType::Int:			return 4;
		case ShaderDataType::Int2:			return 4 * 2;
		case ShaderDataType::Int3:			return 4 * 3;
		case ShaderDataType::Int4:			return 4 * 4;
		case ShaderDataType::Float:			return 4;
		case ShaderDataType::Float2:		return 4 * 2;
		case ShaderDataType::Float3:		return 4 * 3;
		case ShaderDataType::Float4:		return 4 * 4;
		case ShaderDataType::Mat3:			return 4 * 3 * 3;
		case ShaderDataType::Mat4:			return 4 * 4 * 4;
		case ShaderDataType::Bool:			return 1;
		case ShaderDataType::Sampler2D:		return 1;
		}
		
		return 0;
	}

	/**
	\struct BufferElement
	single buffer element, to be stored in a buffer layout
	*/
	struct BufferElement
	{
		std::string Name;//!<name
		ShaderDataType Type;//!<type
		unsigned int Size;//!<size
		size_t Offset;//!<offset
		bool Normalised;//!<normalised

		BufferElement() = default;
		BufferElement(ShaderDataType type, const std::string& name, bool normalised = false) : Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalised(normalised){}

		unsigned int getCompoundCount() const {
			switch (Type) {
			case ShaderDataType::Int:			return 1;
			case ShaderDataType::Int2:			return 2;
			case ShaderDataType::Int3:			return 3;
			case ShaderDataType::Int4:			return 4;
			case ShaderDataType::Float:			return 1;
			case ShaderDataType::Float2:		return 2;
			case ShaderDataType::Float3:		return 3;
			case ShaderDataType::Float4:		return 4;
			case ShaderDataType::Mat3:			return 3 * 3;
			case ShaderDataType::Mat4:			return 4 * 4;
			case ShaderDataType::Bool:			return 1;
			case ShaderDataType::Sampler2D:		return 1;
			}

			return 0;
		}
	};
	/**
	\class BufferLayout
	Contains buffer layout from shader
	*/
	class BufferLayout {
	private:
		std::vector<BufferElement> m_Elements;//!<vector of elements
		unsigned int m_stride = 0;//!<stride
		void calculateOffsetAndStride() {
			size_t offset = 0;
			m_stride = 0;
			for (BufferElement& element : m_Elements) {
				element.Offset = offset;
				offset += element.Size;
				m_stride += element.Size;
			}
		}
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& elements) : m_Elements(elements) {
			calculateOffsetAndStride();
		}
		inline unsigned int getStride() const { return m_stride; }
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		void addElement(BufferElement element);
		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	};

	/**
	\class VertexBuffer
	interface of a VBO
	*/
	class VertexBuffer {
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void Edit(float* vertices, unsigned int size, unsigned int offset) = 0; 

		virtual unsigned int getCount() const = 0;
		virtual const BufferLayout& getLayout() const = 0;
		virtual void setLayout(const BufferLayout& layout) = 0;
		static VertexBuffer* Create(float* vertices, unsigned int size, BufferLayout layout);
		static VertexBuffer* CreateDynamic(unsigned int size, BufferLayout layout);
	};

	/**
	\class IndexBuffer
	interface of a VBO
	*/
	class IndexBuffer {
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void Edit(unsigned int* indicies, unsigned int size, unsigned int offset) = 0;

		virtual unsigned int getCount() const = 0;
		virtual const BufferLayout& getLayout() const = 0;
		virtual void setLayout(const BufferLayout& layout) = 0;
		static IndexBuffer* Create(unsigned int* indicies, unsigned int size);
		static IndexBuffer* CreateDynamic(unsigned int size);
	};

}