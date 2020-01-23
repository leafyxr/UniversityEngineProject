#include "engine_pch.h"
#include "Renderer\Shader.h"
#include "Renderer\RenderAPI.h"
#include "GLFW\GLShader.h"

namespace Engine {

	Shader * Shader::create(const std::string & filepath)
	{
		switch (RenderAPI::getApi()) {
		case RenderAPI::API::None:			return nullptr;
		case RenderAPI::API::OpenGL:		return  new GLShader(filepath);
		}
		return nullptr;
	}

	Shader * Shader::create(const std::string& VertFilepath, const std::string& FragFilepath)
	{
		switch (RenderAPI::getApi()) {
		case RenderAPI::API::None:			return nullptr;
		case RenderAPI::API::OpenGL:		return  new GLShader(VertFilepath, FragFilepath);
		}
		return nullptr;
	}

}