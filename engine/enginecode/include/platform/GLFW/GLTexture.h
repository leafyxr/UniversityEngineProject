/** \file GLTexture.h
*/
#pragma once
#include "Renderer\Texture.h"

namespace Engine {

	/**
	\class GLSuperSimpleRenderer
	GLFW implentation of a Super Simple 3D Renderer
	*/
	class GLTexture : public Texture {
	private:
		std::string m_Path;//!< Path to texture file
		static unsigned int s_Slots;//!< Total number of slots used
		unsigned int m_Width, m_Height, m_Channel, m_Slot;//!< Texture Properties
		unsigned int m_RendererID;//!< Render ID
	public:
		//! Constructor, from file
		/*!
		\param path, path to texture?
		*/
		GLTexture(const std::string& path);
		//! Constructor, from Raw Data
		/*!
		\param width
		\param height
		\param channels
		\param texData, Raw data
		*/
		GLTexture(unsigned int width, unsigned int height, unsigned int channels, unsigned char *texData);
		//! Destructor
		virtual ~GLTexture();

		virtual void bind() override;

		//! get Width
		/*!
		\return width
		*/
		virtual unsigned int getWidth() const override { return m_Width; }
		//! get height
		/*!
		\return height
		*/
		virtual unsigned int getHeight() const override { return m_Height; }
		//! get channels
		/*!
		\return channels
		*/
		virtual unsigned int getChannels() const override { return m_Channel; }
		//! get slot
		/*!
		\return slot
		*/
		virtual unsigned int getSlot() const override { return m_Slot; }

		virtual unsigned int getID() const override { return m_RendererID; }
	};

}