/** \file IMGuiLayer.cpp
*/

#include "engine_pch.h"
#include "include/independent/IMGui/IMGuiLayer.h"

#include <imgui.h>
#include <examples/imgui_impl_opengl3.h>
#include <examples/imgui_impl_glfw.h>

#include "core/application.h"
#include "systems/Codes.h"

// TEMPORARY
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Engine {

	Engine::IMGuiLayerGLFW::IMGuiLayerGLFW() : Layer("IMGuiLayerGLFW")
	{

	}

	IMGuiLayerGLFW::~IMGuiLayerGLFW()
	{

	}
	void IMGuiLayerGLFW::onAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		Application& app = Application::getInstance();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.getWindow().getNativeWindow());

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");

		glm::vec2 res = glm::vec2(app.getWindow().getWidth(), app.getWindow().getHeight());
		io.DisplaySize = ImVec2((float)res.x, (float)res.y);
	}

	void IMGuiLayerGLFW::onDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void IMGuiLayerGLFW::onUpdate(float timestep)
	{
	}

	void IMGuiLayerGLFW::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void IMGuiLayerGLFW::End()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::getInstance();
		io.DisplaySize = ImVec2((float)app.getWindow().getWidth(), (float)app.getWindow().getHeight());

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void IMGuiLayerGLFW::onImGuiRender()
	{
		static bool show = true;

		ImGui::ShowDemoWindow(&show);
	}

}
