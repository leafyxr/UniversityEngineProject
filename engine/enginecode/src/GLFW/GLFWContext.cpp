#include "engine_pch.h"
#include "GLFW\GLFWContext.h"
#include "systems\Log.h"

#include <imgui.h>
#include <examples/imgui_impl_opengl3.h>
#include <examples/imgui_impl_glfw.h>

//#include "IMGui/IMGuiSystem.h"

void Engine::GLFWContext::init()
{
	glfwMakeContextCurrent(m_window);
	int result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	NG_ASSERT(result, "Failed to Initialise GLAD");

	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init("#version 440");
}

void Engine::GLFWContext::swapBuffers()
{
	glfwSwapBuffers(m_window);
}
