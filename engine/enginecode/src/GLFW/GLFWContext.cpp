
#include "engine_pch.h"
#include "GLFW\GLFWContext.h"
#include "systems\Log.h"

void Engine::GLFWContext::init()
{
	glfwMakeContextCurrent(m_window);
	int result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	NG_ASSERT(result, "Failed to Initialise GLAD");
}

void Engine::GLFWContext::swapBuffers()
{
	glfwSwapBuffers(m_window);
}
