/** \file GLFWContext.h
*/
#pragma once
#include "windows/graphicsContext.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Engine {
	/**
	\class GLFWContext
	GLFW implentation of a graphics context
	*/
	class GLFWContext : public GraphicsContext {
	public:
		//! Constructor
		/*!
		\param window, associated window
		*/
		GLFWContext(GLFWwindow* window) : m_window(window) {}
		//! Initialise
		void init() override;
		//! Swap GPU Buffers
		void swapBuffers() override;
	private:
		GLFWwindow * m_window;//!< Pointer to GLFW Window
	};

}