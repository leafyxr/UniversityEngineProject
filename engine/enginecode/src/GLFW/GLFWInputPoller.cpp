#include "engine_pch.h"
#include "GLFW\GLFWInputPoller.h"
#include "core\application.h"

#include "glad\glad.h"
#include "GLFW\glfw3.h"

namespace Engine {

	InputPoller* InputPoller::s_instance = new GLFWInputPoller();

	bool GLFWInputPoller::isKeyPressedImpl(int keycode)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow());
		int result = glfwGetKey(window, keycode);
		return result == KEY_PRESS || result == KEY_REPEAT;
	}
	bool GLFWInputPoller::isMouseButtonPressedImpl(int button)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow());
		int result = glfwGetMouseButton(window, button);
		return result == KEY_PRESS;
	}
	glm::vec2 GLFWInputPoller::getMousePositionImpl()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		return {(int)xPos, (int)yPos};
	}
	float GLFWInputPoller::getMouseXImpl()
	{
		glm::vec2 pos = getMousePositionImpl();
		return (int)pos.x;
	}
	float GLFWInputPoller::getMouseYImpl()
	{
		glm::vec2 pos = getMousePositionImpl();
		return (int)pos.y;
	}
}