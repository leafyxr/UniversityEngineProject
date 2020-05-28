#include "engine_pch.h"
#include "include/independent/IMGui/IMGuiLayer.h"
#include "IMGui/IMGuiSystem.h"

namespace Engine {

	Engine::IMGuiLayer::IMGuiLayer() : Layer("IMGuiLayer")
	{

	}

	IMGuiLayer::~IMGuiLayer()
	{

	}


	void IMGuiLayer::onAttach()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		NG_INFO("TEST");

		std::string curSelection = ("Current Selection = " + std::to_string(0));

		float xPosition[3] = { 0, 0 ,0 };
		float yPosition = 0;
		float zPosition = 0;

		ImGui::Begin("Inspector");
		ImGui::Text(curSelection.c_str());

		ImGui::Text("Position");
		ImGui::InputFloat("X", &xPosition[0], 1);
		ImGui::InputFloat("Y", &xPosition[1], 1);
		ImGui::InputFloat("Z", &xPosition[2], 1);

		ImGui::Text("Rotation");
		ImGui::InputFloat("X", &xPosition[0], 1);
		ImGui::InputFloat("Y", &xPosition[1], 1);
		ImGui::InputFloat("Z", &xPosition[2], 1);

		ImGui::Text("Scale");
		ImGui::InputFloat("X", &xPosition[0], 1);
		ImGui::InputFloat("Y", &xPosition[1], 1);
		ImGui::InputFloat("Z", &xPosition[2], 1);
		ImGui::End();

		ImGuiIO& io = ImGui::GetIO();
		glm::vec2 res = glm::vec2(800, 600);
		io.DisplaySize = ImVec2((float)res.x, (float)res.y);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void IMGuiLayer::onDetach()
	{
		
	}

	void IMGuiLayer::onUpdate(float timestep)
	{
		ImGuiIO& io = ImGui::GetIO();
		glm::vec2 res = glm::vec2(800, 600);
		io.DisplaySize = ImVec2((float)res.x, (float)res.y);
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void IMGuiLayer::onEvent(Event& event)
	{
		
	}

}
