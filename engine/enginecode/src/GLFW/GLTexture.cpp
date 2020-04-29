#include "engine_pch.h"
#include "GLFW\GLTexture.h"
#include "systems/log.h"

#include "stb_image.h"

#include "glad\glad.h"


namespace Engine {

	unsigned int GLTexture::s_Slots = 0;

	GLTexture::GLTexture(const std::string & path) : m_Path(path)
	{
		int width, height, channel;
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channel, 0);
		m_Width = width;
		m_Height = height;
		m_Channel = channel;

		glGenTextures(1, &m_RendererID);
		m_Slot = s_Slots;
		s_Slots++;

		glActiveTexture(GL_TEXTURE0 + m_Slot);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (data)
		{
			if (channel == 3) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			else if (channel == 4) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			else return;
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			return;
		}
		stbi_image_free(data);
		NG_INFO("Texture ID: {0}", m_RendererID);
	}
	GLTexture::GLTexture(unsigned int width, unsigned int height, unsigned int channels, unsigned char * texData) : m_Width(width), m_Height(height), m_Channel(channels)
	{
		glGenTextures(1, &m_RendererID);

		m_Slot = s_Slots;
		s_Slots++;
		if (s_Slots > 16) s_Slots = 0;

		glActiveTexture(GL_TEXTURE0 + m_Slot);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
		glGenerateMipmap(GL_TEXTURE_2D);
		NG_INFO("Texture ID: {0}", m_RendererID);
	}
	GLTexture::~GLTexture()
	{
		glDeleteTextures(1, &m_RendererID);
	}
	void GLTexture::bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}
}