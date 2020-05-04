/** \file GLShader.h
*/
#pragma once
#include "Renderer\Shader.h"

namespace Engine {
	/**
	\class GLSuperSimpleRenderer
	GLFW implentation of a Shader
	*/
	class GLShader : public Shader {
	private:
		unsigned int m_RendererID;//!< Render ID
		std::string m_Name;//!< Name of Shader, Currently Unused
		BufferLayout m_BufferLayout;//!< Buffer Layout
		UniformLayout m_UniformLayout;//!< Uniform Layout

		//! parse source, reads from shader file, extracts relevent data
		/*!
		\param filepath, path to shader code
		*/
		void parseSource(const std::string& filepath);
		//! compile and link shader
		/*!
		\param vert, vertex shader
		\param frag, fragment shader
		*/
		void compileAndLink(std::string Vert, std::string Frag, std::string Geo, std::string TessControl, std::string TessEvaluation);
	public:
		//! Constructor, from one file
		/*!
		\param filepath, path to shader code
		*/
		GLShader(const std::string& filepath);
		//! Constructor, from individual files
		/*!
		\param VertFilepath, path to vertex shader
		\param FragFilepath, path to fragment shader
		*/
		GLShader(const std::string& VertFilepath, const std::string& FragFilepath);

		//! get ID
		/*!
		\return render ID
		*/
		virtual unsigned int id() override { return m_RendererID; }
		//! bind shader to GPU
		virtual void bind() override;
		//! unbind shader from GPU
		virtual void unbind() override;
		//! upload individual data to gpu 
		/*!
		\param name, name of data
		\param data, data to upload
		*/
		virtual bool uploadData(const std::string& name, void* data) override;
		//! upload set of data to gpu
		/*!
		\param uniforms, set of uniform data
		*/
		virtual bool uploadData(const UniformLayout& uniforms) override;
		//! get buffer layout
		/*!
		\return extracted layout from shader code
		*/
		virtual BufferLayout getBufferLayout() const override { return m_BufferLayout; }
		//! get uniform layout
		/*!
		\param last set of data sent to the GPU
		*/
		virtual UniformLayout getUniformLayout() const override { return m_UniformLayout; }

		//! upload Int to gpu 
		/*!
		\param name, name of data
		\param data, data to upload
		*/
		virtual void uploadInt(const std::string& name, int value) override;

		//! upload Float to gpu 
		/*!
		\param name, name of data
		\param data, data to upload
		*/
		virtual void uploadFloat(const std::string& name, float value) override;
		//! upload float vector 2 to gpu 
		/*!
		\param name, name of data
		\param data, data to upload
		*/
		virtual void uploadFloat2(const std::string& name, const glm::vec2& value) override;
		//! upload float vector 3 to gpu 
		/*!
		\param name, name of data
		\param data, data to upload
		*/
		virtual void uploadFloat3(const std::string& name, const glm::vec3& value) override;
		//! upload float vector 4 to gpu 
		/*!
		\param name, name of data
		\param data, data to upload
		*/
		virtual void uploadFloat4(const std::string& name, const glm::vec4& value) override;

		//! upload float matrix 3 to gpu 
		/*!
		\param name, name of data
		\param data, data to upload
		*/
		virtual void uploadMat3(const std::string& name, const glm::mat3& matrix) override;
		//! upload float matrix 4 to gpu 
		/*!
		\param name, name of data
		\param data, data to upload
		*/
		virtual void uploadMat4(const std::string& name, const glm::mat4& matrix) override;
	};

}