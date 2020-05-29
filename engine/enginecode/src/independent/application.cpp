/** \file application.cpp
*/


#include "engine_pch.h"
#include "systems\Log.h"
#include "core\Timer.h"
#include "core/application.h"
#include "systems\InputPoller.h"
#include "systems\Codes.h"
#ifdef NG_PLATFORM_WINDOWS
#include "GLFW/GLFW_Window.h"
#endif // NG_PLATFORM_WINDOWS


namespace Engine {
	Application* Application::s_instance = nullptr;
	bool Application::bActive = true;
	float Application::m_fElapsedTime = 0.0f;

	Application::Application()
	{
		if (s_instance == nullptr)
		{
			s_instance = this;
		}
		Engine::Log::start();
		NG_INFO("Application Starting");
		Engine::Timer::start();

		

#ifdef NG_PLATFORM_WINDOWS
		m_windows = std::shared_ptr<WindowSystem>(new WindowSystemGLFW());
#endif // NG_PLATFORM_WINDOWS
		m_windows->start();
		NG_INFO("Windows system initialised");
		m_Window = std::unique_ptr<Window>(Window::create());
		m_Window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
		m_audioManager.reset(new AudioManager());
		m_audioManager->start();
		NG_INFO("audio manager started");
		ImGuiLayer = std::make_unique<IMGuiLayerGLFW>();
		ImGuiLayer->onAttach();
	}

	Application::~Application()
	{
		ImGuiLayer->onDetach();
		NG_INFO("Audio Stopped");
		m_audioManager->stop();
		NG_INFO("Application Exiting");
		m_layerStack.stop();
		NG_INFO("Layers Closed");
		m_windows->stop();
		NG_INFO("Windows Closed");
		Engine::Timer::stop();
		NG_INFO("Timer Stopped");

	}

	

	void Application::run()
	{
		while (bActive) {
			Engine::Timer::update();
			float timestep = Engine::Timer::GetFrameSeconds();
			m_fElapsedTime += timestep;
			float FPS = 1.0f / timestep;
			//NG_INFO("FPS: {0}, Elapsed Time : {1}", FPS, m_fElapsedTime);
			int i = 0;
			for (auto it = m_layerStack.begin(); it != m_layerStack.end(); it++)
			{
				//NG_INFO("Layer: {0} loaded #{1}", (*it)->getName(), i);
				(*it)->onUpdate(timestep);
				i++;
			}

			ImGuiLayer->Begin();
			ImGuiLayer->onImGuiRender();
			for (auto it = m_layerStack.begin(); it != m_layerStack.end(); it++)
			{
				//NG_INFO("Layer: {0} loaded #{1}", (*it)->getName(), i);
				(*it)->onImGuiRender();
				i++;
			}
			ImGuiLayer->End();

			m_Window->onUpdate(timestep);
			if (InputPoller::isKeyPressed(KEY_ESCAPE)) bActive = false;
			m_audioManager->update();
		}
	}

	void Application::onEvent(Event & e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::onClose, this, std::placeholders::_1));
		dispatcher.dispatch<WindowResizeEvent>(std::bind(&Application::onResize, this, std::placeholders::_1));
		dispatcher.dispatch<WindowFocusEvent>(std::bind(&Application::onFocus, this, std::placeholders::_1));
		dispatcher.dispatch<WindowLostFocusEvent>(std::bind(&Application::onFocusLost, this, std::placeholders::_1));
		dispatcher.dispatch<WindowMovedEvent>(std::bind(&Application::onWindowMoved, this, std::placeholders::_1));

		for (auto it = m_layerStack.begin(); it != m_layerStack.end(); it++) {
			(*it)->onEvent(e);
			if (e.handled()) break;
		}
	}

	bool Application::onClose(WindowCloseEvent & e)
	{
		NG_INFO("Closing Application");
		bActive = false;
		return true;
	}

	bool Application::onResize(WindowResizeEvent & e)
	{
		m_Window->onResize(e.getWidth(), e.getHeight());
		return false;
	}

	bool Application::onFocus(WindowFocusEvent & e)
	{
		//NG_INFO("Window Focused at {0}, {1}", e.getXPos(), e.getYPos());
		return false;
	}

	bool Application::onFocusLost(WindowLostFocusEvent & e)
	{
		//NG_INFO("Window Lost Focus at {0}, {1}", e.getXPos(), e.getYPos());
		return false;
	}

	bool Application::onWindowMoved(WindowMovedEvent & e)
	{
		//NG_INFO("Window Moved to {0}, {1}", e.getXPos(), e.getYPos());
		return false;
	}

	void Application::PushLayer(Layer* layer)
	{
		m_layerStack.push(layer);
		layer->onAttach();
	}
}