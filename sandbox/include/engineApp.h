/** \file engineApp.h
*/
#pragma once

#include <Engine.h>


/**
\class GameLayer
layer containing all game related objects (3D)
*/
class GameLayer : public Engine::Layer {
private:
	std::shared_ptr<Engine::ResourceManager> m_resManager; //!< a Resource Manager
	std::vector<std::shared_ptr<Engine::GameObject>> m_gameObjects; 
	std::vector<std::shared_ptr<Engine::MaterialComponent>> m_materials;
	std::vector<std::shared_ptr<Engine::PositionComponent>> m_positions;;
	std::vector<std::shared_ptr<Engine::VelocityComponent>> m_velocities; 
	std::vector<std::shared_ptr<Engine::OscilateComponent>> m_oscilation;

	glm::mat4 m_FCmodel, m_TPmodel; //!< Model Matrices
	Engine::OscilateComponent::state m_FCstate, m_TPstate;

	std::shared_ptr<Engine::AudioManager> m_audioManager; //!< Audio Manager
	bool m_goingUp = false; //!< Cube Going Up
	float m_timeSummed = 10.f; //!< Time before changing Direction
	float m_elapsedTime = 0.0f;
	float m_Framerate = 0;

	//! Framebuffer Picking Variables
	int m_Body = 0, m_currentSelection = 0;

	//!Selected Component Transform Values
	glm::vec3 m_Position, m_Rotation, m_Scale;
	bool isTextured = false;
	std::vector<std::string> m_Textures;
	//!Light Parameters
	glm::vec3 m_LightPos, m_LightColor;

	float m_VolumeAudio = 0;

public:

	//! Constructor
	/*!
		\param name, Layer Name
	*/
	GameLayer(const std::string& name = "Layer") : Layer(name) {};
	//! Run when attached to LayerStack
	void onAttach() override;
	//! Run before Deletion
	void onDetach() override;
	//! Run on Update
	/*!
		\param timestep, time since last frame
	*/
	void onUpdate(float timestep) override;
	//! Run on Event
	/*!
	\param event, Event type occuring
	*/
	void onEvent(Engine::Event& event) override;
	//! On Mouse Moved event
	bool onMouseMoved(Engine::MouseMovedEvent);
	//! On Resize Event
	bool onResize(Engine::WindowResizeEvent);
	//! On ImGui Render
	void onImGuiRender() override;
	//! Creates a flat cube prefab at the origin
	void createFlatCube();
	//! Creates a textured cube prefab at the origin
	void createTexturedCube();

};

/**
\class TextLayer
layer containing all Text related objects (2D) Currently Non-Functional
*/
class TextLayer : public Engine::Layer {
private:
	std::shared_ptr<Engine::Text> m_Text;
	std::shared_ptr<Engine::Texture> m_Texture;
	std::shared_ptr<Engine::ResourceManager> m_resManager;
	std::shared_ptr<Engine::Shader> m_Shader;
	std::shared_ptr<Engine::VertexArray> m_VAOText;
	std::shared_ptr<Engine::VertexBuffer> m_VBOText;
	std::shared_ptr<Engine::Material> m_Material;
	
public:
	//! Constructor
	/*!
	\param name, Layer Name
	*/
	TextLayer(const std::string& name = "Layer") : Layer(name) {};
	//! Run when attached to LayerStack
	void onAttach() override;
	//! Run before Deletion
	void onDetach() override;
	//! Run on Update
	/*!
	\param timestep, time since last frame
	*/
	void onUpdate(float timestep) override;
	//! Run on Event
	/*!
	\param event, Event type occuring
	*/
	void onEvent(Engine::Event& event) override;
	//! On ImGui Render
	void onImGuiRender() override;

};

/**
\class engineApp
subclass of engine for Sandbox Application
*/
class engineApp : public Engine::Application
{
public:
	//! Constructor
	engineApp();
	//! Deconstructor
	~engineApp() override;
};
