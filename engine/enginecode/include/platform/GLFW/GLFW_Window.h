/** \file GLFW_Window.h
*/
#pragma once
#include "windows\window.h"
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

namespace Engine {
	/**
	\class WindowSystemGLFW
	GLFW Implementation of a window system, Initilises GLFW 
	*/
	class WindowSystemGLFW : public WindowSystem {
	private:
		static bool s_active;//!< Flat Colour Material
	public:
		//! Start System
		void start(SystemSignal init = SystemSignal::None, ...) override;
		//! Stop System
		void stop(SystemSignal init = SystemSignal::None, ...) override;
		//! Get active
		/*!
		\return is System Active
		*/
		inline bool isActive() const override { return s_active; };
	};
	/**
	\class WindowWindow
	GLFW implentation of a window
	*/
	class WindowsWindow : public Window {
	private:
		GLFWwindow * m_nativeWindow;//!< Pointer to GLFW Window

		//! Initialiser
		/*!
		
		*/
		void init(const WindowProperties& properties) override;
		//! Close Window
		void close();
		float m_AspectRatio;//!< Aspect Ratio of Window

		struct WindowData : WindowProperties//!< Struct Containing all Window data, Inherits from Windows Properties
		{
			std::function<void(Event&)> m_EventCallback;//!< Link to Event Callback
		};
		WindowData m_Data;//!< Window Data
	public:
		//! Constructor
		/*!
		\param properties, properties of window to create
		*/
		WindowsWindow(const WindowProperties& properties);
		//! Destructor
		~WindowsWindow();
		//! On Update
		/*!
		\param timestep, time since last frame
		*/
		void onUpdate(float timestep) override;
		//! on Resize
		/*!
		\param width, new window width;
		\param height, new window height
		*/
		void onResize(unsigned int width, unsigned int height) override;
		//! set Vsync
		/*!
		\param Vsync, enable or disable
		*/
		void setVSync(bool VSync) override;
		//! Set Event Callback
		/*!
		\param callback, set to an event callback
		*/
		void setEventCallback(const std::function<void(Event&)>& callback) override;
		//! get Width
		/*!
		\return width of window
		*/
		inline unsigned int getWidth() const override { return m_Data.m_width; }
		//! get height
		/*!
		\return height of window
		*/
		inline unsigned int getHeight() const override { return m_Data.m_height; }
		//! get native window
		/*!
		\return used window
		*/
		inline void* getNativeWindow() const override { return m_nativeWindow; }
		//! Is window fullscreen
		/*!
		\return If window fullscreen
		*/
		inline bool isFullScreenMode() const override { return m_Data.m_isFullScreen; }
		//! is Vsync enabled
		/*!
		\return if Vsync enabled
		*/
		inline bool isVSync() const override { return m_Data.m_isVSync; }
	};

}