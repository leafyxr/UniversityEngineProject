#include "engine_pch.h"
#include "Renderer\Texture.h"
#include "Renderer\RenderAPI.h"
#include "GLFW\GLTexture.h"

namespace Engine {

	Texture * Texture::createFromFile(const std::string & filepath)
	{
		switch (RenderAPI::getApi()) {
		case RenderAPI::API::None:			return nullptr;
		case RenderAPI::API::OpenGL:		return  new GLTexture(filepath);
		}
		return nullptr;
	}

	Texture * Texture::createFromRawData(unsigned int width, unsigned int height, unsigned int channels, unsigned char * texData)
	{
		return nullptr;
	}

}