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
	std::shared_ptr<Engine::Material> m_FCmaterial;//!< Flat Colour Material
	std::shared_ptr<Engine::Material> m_TPmaterial;//!< Textured Phong Material
	//std::shared_ptr<Engine::VertexArray> m_FCvertexArray;//!< Flat Colour VAO
	//std::shared_ptr<Engine::VertexBuffer> m_FCvertexBuffer;//!< Textured Phong VBO
	std::shared_ptr<Engine::VertexArray> m_TPvertexArray;//!< Flat Colour VAO
	std::shared_ptr<Engine::VertexBuffer> m_TPvertexBuffer;//!< Textured Phong ABO
	//std::shared_ptr<Engine::IndexBuffer> m_FCindexBuffer;//!< Flat Colour Index Buffer
	std::shared_ptr<Engine::IndexBuffer> m_TPindexBuffer;//!< Textured Phong Index Buffer
	//std::shared_ptr<Engine::Shader> m_FCprogram;//!< Flat Colour Shader ID
	std::shared_ptr<Engine::Shader> m_TPprogram;//!< Textured Phong Shader ID
	std::shared_ptr<Engine::Texture> m_numberTexture;//!< Number Texture
	std::shared_ptr<Engine::Texture> m_letterTexture;//!< Letter Texture
	glm::mat4 m_FCmodel, m_TPmodel; //!< Model Matrices

	bool m_goingUp = false; //!< Cube Going Up
	float m_timeSummed = 10.f; //!< Time before changing Direction
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
};

/**
\class TextLayer
layer containing all Text related objects (2D)
*/
class TextLayer : public Engine::Layer {
private:
	std::shared_ptr<Engine::ResourceManager> m_resManager;
	std::shared_ptr<Engine::Shader> m_Shader;
	std::shared_ptr<Engine::VertexArray> m_VAO;
	std::shared_ptr<Engine::VertexBuffer> m_VBO;
	std::shared_ptr<Engine::IndexBuffer> m_indexBuffer;
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
