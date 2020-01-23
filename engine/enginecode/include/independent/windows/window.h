/** \file window.h
*/
#pragma once
#include "systems\log.h"
#include "graphicsContext.h"
#include <string>
#include <functional>

namespace Engine {

	/**
	\class WindowSystem
	Interface class for a window system
	*/
	class WindowSystem : public System{
	private:
	public:
		//! Start
		virtual void start(SystemSignal init = SystemSignal::None, ...) = 0;
		//! Stop
		virtual void stop(SystemSignal init = SystemSignal::None, ...) = 0;
		//! is active
		/*!
		\return is Active?
		*/
		virtual bool isActive() const = 0;
	};

	/**
	\struct WindowProperties
	*/
	struct WindowProperties
	{
		std::string m_title;//!< Window title
		unsigned int m_width;//!< Window Width
		unsigned int m_height;//!< Window Height
		bool m_isFullScreen;//!< is fullscreen
		bool m_isVSync;//!< is Vsync

		//! Constructor
		/*!
		\param title
		\param width
		\param height
		\param fullscreen
		*/
		WindowProperties(const std::string& title = "My Window", unsigned int width = 800, unsigned int height = 600, bool fullscreen = false) : m_title(title), m_width(width), m_height(height), m_isFullScreen(fullscreen) {}
	};

	/**
	\class Window
	Interface class for a Window
	*/
	class Window
	{
	public:
		//! Initialiser
		/*!
		\param properties
		*/
		virtual void init(const WindowProperties& properties) = 0;
		//! close
		virtual void close() = 0;
		//! destructor
		virtual ~Window() {};
		//! on Update
		/*!
		\param timestep, time since last frame
		*/
		virtual void onUpdate(float timestep) = 0;
		//! on Resize
		/*!
		\param width
		\param height
		*/
		virtual void onResize(unsigned int width, unsigned int height) = 0;
		//! Vsync
		/*!
		\param vsync, true/false
		*/
		virtual void setVSync(bool VSync) = 0;
		//! set Event Callback
		/*!
		\param callback
		*/
		virtual void setEventCallback(const std::function<void(Event&)>& callback) = 0;
		//! get Width
		/*!
		\return width
		*/
		virtual unsigned int getWidth() const = 0;
		//! get height
		/*!
		\return height
		*/
		virtual unsigned int getHeight() const = 0;
		//! get native window
		/*!
		\return window
		*/
		virtual void* getNativeWindow() const = 0;
		//! get fullscreen
		/*!
		\return if fullscreen
		*/
		virtual bool isFullScreenMode() const = 0;
		//! get Vsync
		/*!
		\return is Vsync
		*/
		virtual bool isVSync() const = 0;

		//! Create Window
		/*!
		\param properties, window properties
		\return created window 
		*/
		static Window* create(const WindowProperties& properties = WindowProperties());
	protected:
		std::shared_ptr<GraphicsContext> m_context;//!< Graphics Context
	};
}

