#pragma once
#include "engine_pch.h"
#include "systems/log.h"

#include "events\WindowEvents.h"
#include "events\KeyEvents.h"
#include "events\MouseEvents.h"
#include "GLFW\GLFW_Window.h"
#include "GLFW\GLFWContext.h"
namespace Engine {

	static void GLFWErrorCallback(int error, const char* desc) {
		NG_ERROR("GLFW Error ({0}): {1}", error, desc);
	}

	Window* Window::create(const WindowProperties& properites) {
		return new WindowsWindow(properites);
	}

	void WindowsWindow::init(const WindowProperties & properties)
	{
		m_Data.m_title = properties.m_title;
		m_Data.m_width = properties.m_width;
		m_Data.m_height = properties.m_height;
		m_Data.m_isVSync = properties.m_isVSync;
		m_Data.m_isFullScreen = properties.m_isFullScreen;

		NG_INFO("Creating window {0} ({1}x{2})", properties.m_title, properties.m_width, properties.m_height);

		m_nativeWindow = glfwCreateWindow((int)properties.m_width, (int)properties.m_height, m_Data.m_title.c_str(), nullptr, nullptr);

		m_context = std::make_unique<GLFWContext>(m_nativeWindow);
		m_context->init();

		glfwSetWindowUserPointer(m_nativeWindow, &m_Data);
		setVSync(properties.m_isVSync);

		glfwSetWindowSizeCallback(m_nativeWindow, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.m_width = width;
			data.m_height = height;

			WindowResizeEvent event(width, height);
			data.m_EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_nativeWindow, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.m_EventCallback(event);
		});

		glfwSetKeyCallback(m_nativeWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				KeyPressedEvent event(key, 0);
				data.m_EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(key);
				data.m_EventCallback(event);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent event(key, 1);
				data.m_EventCallback(event);
				break;
			}
			}
		});

		glfwSetCharCallback(m_nativeWindow, [](GLFWwindow* window, unsigned int keycode)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(keycode);
			data.m_EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_nativeWindow, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(button);
				data.m_EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(button);
				data.m_EventCallback(event);
				break;
			}
			}
		});

		glfwSetScrollCallback(m_nativeWindow, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.m_EventCallback(event);
		});

		glfwSetCursorPosCallback(m_nativeWindow, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.m_EventCallback(event);
		});

		glfwSetWindowFocusCallback(m_nativeWindow, [](GLFWwindow* window, int focused)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			int xpos, ypos;
			glfwGetWindowPos(window, &xpos, &ypos);
			if (focused) {
				WindowFocusEvent event(xpos, ypos);
				data.m_EventCallback(event);
				return;
			}
			else {
				WindowLostFocusEvent event(xpos, ypos);
				data.m_EventCallback(event);
				return;
			}
			
		});

		glfwSetWindowPosCallback(m_nativeWindow, [](GLFWwindow* window, int xPos, int yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowMovedEvent event((int)xPos, (int)yPos);
			data.m_EventCallback(event); 
		});
	}

	void WindowsWindow::close()
	{
		glfwDestroyWindow(m_nativeWindow);
	}

	WindowsWindow::WindowsWindow(const WindowProperties & properties)
	{
		init(properties);
	}

	WindowsWindow::~WindowsWindow()
	{
		close();
	}

	void WindowsWindow::onUpdate(float timestep)
	{
		glfwPollEvents();
		m_context->swapBuffers();
	}

	void WindowsWindow::onResize(unsigned int width, unsigned int height)
	{
		m_Data.m_height = height;
		m_Data.m_width = width;
	}

	void WindowsWindow::setVSync(bool VSync)
	{
		if (VSync) glfwSwapInterval(1);
		else glfwSwapInterval(0);

		m_Data.m_isVSync = VSync;
	}

	void WindowsWindow::setEventCallback(const std::function<void(Event&)>& callback)
	{
		m_Data.m_EventCallback = callback;
	}

	//Window System

	bool WindowSystemGLFW::s_active = false;

	void WindowSystemGLFW::start(SystemSignal init, ...)
	{
		if (!s_active) {
			NG_INFO("Initialising GLFW");
			int success = glfwInit();
			NG_ASSERT(success, "Could not Initialise GLFW");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_active = true;
		}
	}

	void WindowSystemGLFW::stop(SystemSignal init, ...)
	{
		if (s_active)
		{
			s_active = false;
			NG_INFO("Terminating GLFW");
			glfwTerminate();
		}
	}

}