/** \file application.h
*/
#pragma once

#include "systems/resourceManager.h"
#include "IMGui/IMGuiSystem.h"
#include "events\Event.h"
#include "events\WindowEvents.h"
#include "events\KeyEvents.h"
#include "events\MouseEvents.h"
#include "windows/window.h"
#include "Renderer\Layer.h"

#include "Audio/AudioManager.h"

namespace Engine {

	/**
	\class Application
	Fundemental class of the engine. A singleton which runs the game loop infinitely.
	Provides ...
	*/

	class Application
	{
	protected:
		Application(); //!< Constructor
		std::shared_ptr<WindowSystem> m_windows;//!< Windows system
		std::unique_ptr<Window> m_Window;//!< Window
		Layerstack m_layerStack;
		std::shared_ptr<AudioManager> m_audioManager;
	private:
		static float m_fElapsedTime;//!< How long the application has been running for
		static bool bActive;//!< Is application running
		static Application* s_instance; //!< Singleton instance of the application

		std::shared_ptr<IMGuiSystem> m_imguiSystem; //!< TODO: Comment

	public:
		virtual ~Application(); //!< Deconstructor
		inline static Application& getInstance() { return *s_instance; } //!< Instance getter from singleton pattern
		void run(); //!< Main loop
		void onEvent(Event& e);
		bool onClose(WindowCloseEvent& e);
		//!Window Events
		bool onResize(WindowResizeEvent& e);
		bool onFocus(WindowFocusEvent& e);
		bool onFocusLost(WindowLostFocusEvent& e);
		bool onWindowMoved(WindowMovedEvent& e);
		void Application::PushLayer(Layer* layer);

		int getScreenRes(float, float);

		inline Window& getWindow() { return *m_Window; }
		std::shared_ptr<AudioManager> getAudio() { return m_audioManager; }
	};

	// To be defined in users code
	Application* startApplication(); //!< Function definition which provides an entry hook

}