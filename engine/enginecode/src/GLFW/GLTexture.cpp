#include "engine_pch.h"
#include "GLFW\GLTexture.h"
#include "systems/log.h"

#include "stb_image.h"

#include "glad\glad.h"


namespace Engine {

	GLTexture::GLTexture(const std::string & path) : m_Path(path)
	{
		int width, height, channel;
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channel, 0);

		GLenum internalFormat, dataFormat;

		if (data)
		{
			if (channel == 3) 
			{
				internalFormat = GL_RGB8;
				dataFormat = GL_RGB;
			}
			else if (channel == 4)
			{
				internalFormat = GL_RGBA8;
				dataFormat = GL_RGBA;
			}
			else return;
		}
		else
		{
			return;
		}


		m_Width = width;
		m_Height = height;
		m_Channel = channel;

		glCreateTextures(GL_TEXTURE_2D, 1,&m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);
		
		stbi_image_free(data);
		NG_INFO("Texture ID: {0}", m_RendererID);
	}
	GLTexture::GLTexture(unsigned int width, unsigned int height, unsigned int channels, unsigned char * texData) : m_Width(width), m_Height(height), m_Channel(channels)
	{
		glCreateTextures(GL_TEXTURE_2D, 1 ,&m_RendererID);
		glTextureStorage2D(m_RendererID, 1, GL_RED, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, GL_RED, GL_UNSIGNED_BYTE, texData);

		NG_INFO("Texture ID: {0}", m_RendererID);
	}
	GLTexture::~GLTexture()
	{
		glDeleteTextures(1, &m_RendererID);
	}
	void GLTexture::bind(unsigned int slot)
	{
		NG_INFO("Bind Texture ID: {0} to Slot = {1}", m_RendererID, slot);
		glBindTextureUnit(slot, m_RendererID);
	}
}