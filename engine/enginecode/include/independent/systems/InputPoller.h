/** \file InputPoller.h
*/
#pragma once
#include <glm/glm.hpp>
#include "systems\Codes.h"

namespace Engine {
	/**
	\class InputPoller
	Interface for Input Polling
	*/
	class InputPoller {
	private:
		static InputPoller* s_instance;//!< singleton Instance of input poller
	protected:
		//! is key pressed
		/*!
		\param keycode, key to check
		\return is key pressed
		*/
		virtual bool isKeyPressedImpl(int keycode) = 0;
		//! is mouse pressed
		/*!
		\param button, button to check
		\return is button pressed
		*/
		virtual bool isMouseButtonPressedImpl(int button) = 0;
		//! get mouse position
		/*!
		\return mouse position
		*/
		virtual glm::vec2 getMousePositionImpl() = 0;
		//! get mouse x position
		/*!
		\return mouse x position
		*/
		virtual float getMouseXImpl() = 0;
		//! get mouse y position
		/*!
		\return mouse y position
		*/
		virtual float getMouseYImpl() = 0;
	public:
		//! is key pressed
		/*!
		\param keycode, key to check
		\return is key pressed
		*/
		inline static bool isKeyPressed(int keycode) { return s_instance->isKeyPressedImpl(keycode); }
		//! is mouse pressed
		/*!
		\param button, button to check
		\return is button pressed
		*/
		inline static bool isMouseButtonPressed(int button) { return s_instance->isMouseButtonPressedImpl(button); }
		//! get mouse position
		/*!
		\return mouse position
		*/
		inline static glm::vec2 getMousePosition() { return s_instance->getMousePositionImpl(); }
		//! get mouse x position
		/*!
		\return mouse x position
		*/
		inline static float getMouseX() { return s_instance->getMouseXImpl(); }
		//! get mouse y position
		/*!
		\return mouse y position
		*/
		inline static float getMouseY() { return s_instance->getMouseYImpl(); }
	};


}