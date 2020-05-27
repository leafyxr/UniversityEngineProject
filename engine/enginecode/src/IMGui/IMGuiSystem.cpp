/** \file IMGuiSystem.cpp
*/
#include "engine_pch.h"
#include "IMGui/IMGuiSystem.h"
//#include "src/IMGui/IMGuiBuild.cpp"

namespace Engine {
	void IMGuiSystem::start(SystemSignal sig, ...)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		ImGui::StyleColorsClassic();
	}

	void IMGuiSystem::stop(SystemSignal sig, ...)
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
	}
}