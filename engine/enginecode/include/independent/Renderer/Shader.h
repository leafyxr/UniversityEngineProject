/** \file Shader.h
*/
#pragma once
#include <map>
#include "Buffer.h"
#include "glm\glm.hpp"

namespace Engine {

	using UniformLayout = std::map<std::string, void*>;

	/**
	\class Shader
	Interface for shader 
	*/
	class Shader {
	public:
		//! get ID
		/*!
		\return ID
		*/
		virtual unsigned int id() = 0;
		//! Bind to GPU
		virtual void bind() = 0;
		//! Unbind from GPU
		virtual void unbind() = 0;
		//! upload individual data to gpu 
		/*!
		\param name, name of data
		\param data, data to upload
		*/
		virtual bool uploadData(const std::string& name, void* data) = 0;
		//! upload set of data to gpu
		/*!
		\param uniforms, set of uniform data
		*/
		virtual bool uploadData(const UniformLayout& uniforms) = 0;
		//! get buffer layout
		/*!
		\return extracted layout from shader code
		*/
		virtual BufferLayout getBufferLayout() const = 0;
		//! get uniform layout
		/*!
		\param last set of data sent to the GPU
		*/
		virtual UniformLayout getUniformLayout() const = 0;

		//! upload Int to gpu 
		/*!
		\param name, name of data
		\param data, data to upload
		*/
		virtual void uploadInt(const std::string& name, int value) = 0;

		//! upload Float to gpu 
		/*!
		\param name, name of data
		\param data, data to upload
		*/
		virtual void uploadFloat(const std::string& name, float value) = 0;
		//! upload float vector 2 to gpu 
		/*!
		\param name, name of data
		\param data, data to upload
		*/
		virtual void uploadFloat2(const std::string& name, const glm::vec2& value) = 0;
		//! upload float vector 3 to gpu 
		/*!
		\param name, name of data
		\param data, data to upload
		*/
		virtual void uploadFloat3(const std::string& name, const glm::vec3& value) = 0;
		//! upload float vector 4 to gpu 
		/*!
		\param name, name of data
		\param data, data to upload
		*/
		virtual void uploadFloat4(const std::string& name, const glm::vec4& value) = 0;

		//! upload float matrix 3 to gpu 
		/*!
		\param name, name of data
		\param data, data to upload
		*/
		virtual void uploadMat3(const std::string& name, const glm::mat3& matrix) = 0;
		//! upload float matrix 4 to gpu 
		/*!
		\param name, name of data
		\param data, data to upload
		*/
		virtual void uploadMat4(const std::string& name, const glm::mat4& matrix) = 0;

		//! create from one file
		/*!
		\param filepath, path to shader code
		*/
		static Shader* create(const std::string& filepath);
		//! create from individual files
		/*!
		\param VertFilepath, path to vertex shader
		\param FragFilepath, path to fragment shader
		*/
		static Shader* create(const std::string& VertFilepath, const std::string& FragFilepath);
	};
}

//gl patches, change above function