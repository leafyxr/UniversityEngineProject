/** \file Texture.h
*/
#pragma once

namespace Engine {
	/**
	\class Texture
	Interface for Texture
	*/
	class Texture {
	public:

		virtual void bind(unsigned int slot) = 0;

		//! get width
		/*!
		\return width
		*/
		virtual unsigned int getWidth() const = 0;
		//! get height
		/*!
		\return height
		*/
		virtual unsigned int getHeight() const = 0;
		//! get Channels
		/*!
		\return Channels
		*/
		virtual unsigned int getChannels() const = 0;
		//! get slot
		/*!
		\return slot
		*/

		virtual unsigned int getID() const = 0;

		virtual std::string getPath() = 0;

		//! create from file
		/*!
		\return filepath
		*/
		static Texture *createFromFile(const std::string& filepath);
		//! create from Raw Data
		/*!
		\param width
		\param height
		\param channels
		\param texData, Raw data
		*/
		static Texture *createFromRawData(unsigned int width, unsigned int height, unsigned int channels, unsigned char *texData);
	};

}