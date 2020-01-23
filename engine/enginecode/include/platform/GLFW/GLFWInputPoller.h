/** \file GLFWInputPoller.h
*/
#pragma once
#include "systems\InputPoller.h"

namespace Engine {
	/**
	\class GLFWInputPoller
	GLFW implementation of an Input Poller
	*/
	class GLFWInputPoller : public InputPoller {
	protected:
		//! is Key Pressed
		/*!
		\param keycode, key to check
		\return if key is pressed
		*/
		bool isKeyPressedImpl(int keycode) override;
		//! is Mouse Pressed
		/*!
		\param button, button to check
		\return if button is pressed
		*/
		bool isMouseButtonPressedImpl(int button) override;
		//! get Mouse Position
		glm::vec2 getMousePositionImpl() override;
		//! Get Mouse X Postition
		float getMouseXImpl() override;
		//! Get Mouse Y Postition
		float getMouseYImpl() override;
	};

}