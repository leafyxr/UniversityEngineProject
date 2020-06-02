/** \file engineApp.cpp
*/
#include "engineApp.h"
#include "IMGui.h"

#include "flatCube.h"
#include "texturedPhongCube.h"

#include "systems/InputPoller.h"

//!Game Layer Definitions

void GameLayer::onAttach()
{
	//!Init renderer
	m_renderer = std::shared_ptr<Engine::Renderer>(Engine::Renderer::createPostProcess3D());
	//!Init Camera
	m_camera = std::shared_ptr<Engine::FPSCameraControllerEuler>(new Engine::FPSCameraControllerEuler()); 

	m_camera->init(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	m_camera->setPosition(glm::vec3(0.f, 0.f, 10.f));

	float FCvertices[6 * 24] = {
	-0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.2f, // red square
	0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.2f,
	0.5f,  0.5f, -0.5f, 0.8f, 0.2f, 0.2f,
	-0.5f,  0.5f, -0.5f,  0.8f, 0.2f, 0.2f,
	-0.5f, -0.5f, 0.5f, 0.2f, 0.8f, 0.2f, // green square
	0.5f, -0.5f, 0.5f, 0.2f, 0.8f, 0.2f,
	0.5f,  0.5f, 0.5f, 0.2f, 0.8f, 0.2f,
	-0.5f,  0.5f, 0.5f,  0.2f, 0.8f, 0.2f,
	-0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.8f, // magenta(ish) square
	0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.8f,
	0.5f, -0.5f, 0.5f, 0.8f, 0.2f, 0.8f,
	-0.5f, -0.5f, 0.5f,  0.8f, 0.2f, 0.8f,
	-0.5f, 0.5f, -0.5f, 0.8f, 0.8f, 0.2f, // yellow square
	0.5f, 0.5f, -0.5f, 0.8f, 0.8f, 0.2f,
	0.5f, 0.5f, 0.5f, 0.8f, 0.8f, 0.2f,
	-0.5f, 0.5f, 0.5f,  0.8f, 0.8f, 0.2f,
	-0.5f, -0.5f, -0.5f, 0.2f, 0.8f, 0.8f, // Cyan(ish) square
	-0.5f,  0.5f, -0.5f,  0.2f, 0.8f, 0.8f,
	-0.5f,  0.5f, 0.5f, 0.2f, 0.8f, 0.8f,
	-0.5f,  -0.5f, 0.5f, 0.2f, 0.8f, 0.8f,
	0.5f, -0.5f, -0.5f, 0.2f, 0.2f, 0.8f, // Blue square
	0.5f,  0.5f, -0.5f,  0.2f, 0.2f, 0.8f,
	0.5f,  0.5f, 0.5f, 0.2f, 0.2f, 0.8f,
	0.5f,  -0.5f, 0.5f, 0.2f, 0.2f, 0.8f
	};

	unsigned int CubeIndices[3 * 12] = {
	2, 1, 0,
	0, 3, 2,
	4, 5, 6,
	6, 7, 4,
	8, 9, 10,
	10, 11, 8,
	14, 13, 12,
	12, 15, 14,
	18, 17, 16,
	16, 19, 18,
	20, 21, 22,
	22, 23, 20
	};

	float TPvertices[8 * 24] = {
	-0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f, 0.33f, 0.5f,
	0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f, 0.f, 0.5f,
	0.5f,  0.5f, -0.5f, 0.f, 0.f, -1.f, 0.f, 0.f,
	-0.5f,  0.5f, -0.5f, 0.f, 0.f, -1.f, 0.33f, 0.f,
	-0.5f, -0.5f, 0.5f,  0.f, 0.f, 1.f, 0.33f, 0.5f,
	0.5f, -0.5f, 0.5f,  0.f, 0.f, 1.f, 0.66f, 0.5f,
	0.5f,  0.5f, 0.5f,  0.f, 0.f, 1.f, 0.66f, 0.f,
	-0.5f,  0.5f, 0.5f,  0.f, 0.f, 1.f, 0.33, 0.f,
	-0.5f, -0.5f, -0.5f, 0.f, -1.f, 0.f, 1.f, 0.f,
	0.5f, -0.5f, -0.5f, 0.f, -1.f, 0.f, 0.66f, 0.f,
	0.5f, -0.5f, 0.5f,  0.f, -1.f, 0.f, 0.66f, 0.5f,
	-0.5f, -0.5f, 0.5f,  0.f, -1.f, 0.f, 1.0f, 0.5f,
	-0.5f, 0.5f, -0.5f,  0.f, 1.f, 0.f, 0.33f, 1.0f,
	0.5f, 0.5f, -0.5f,  0.f, 1.f, 0.f, 0.f, 1.0f,
	0.5f, 0.5f, 0.5f, 0.f, 1.f, 0.f, 0.f, 0.5f,
	-0.5f, 0.5f, 0.5f,   0.f, 1.f, 0.f, 0.3f, 0.5f,
	-0.5f, -0.5f, -0.5f, -1.f, 0.f, 0.f, 0.33f, 1.0f,
	-0.5f,  0.5f, -0.5f, -1.f, 0.f, 0.f, 0.33f, 0.5f,
	-0.5f,  0.5f, 0.5f,  -1.f, 0.f, 0.f, 0.66f, 0.5f,
	-0.5f,  -0.5f, 0.5f, -1.f, 0.f, 0.f, 0.66f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.f, 0.f, 0.f, 1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.f, 0.f, 0.f, 1.0f, 0.5f,
	0.5f,  0.5f, 0.5f, 1.f, 0.f, 0.f,  0.66f, 0.5f,
	0.5f,  -0.5f, 0.5f,  1.f, 0.f, 0.f, 0.66f, 1.0f
	};

	m_resManager.reset(new Engine::ResourceManager());
	//!fc cube res. manager code
	m_resManager->addShader("flatColour","assets/shaders/flatColourTess.glsl"); 
	m_resManager->addVertexArray("FCcube");
	m_resManager->getVertexArrayType().get("FCcube")->addVertexBuffer(m_resManager->addVertexBuffer("FCVBO", FCvertices, sizeof(FCvertices), m_resManager->getShaderType().get("flatColour")->getBufferLayout()));
	m_resManager->getVertexArrayType().get("FCcube")->addIndexBuffer(m_resManager->addIndexBuffer("FCIBO", CubeIndices, sizeof(CubeIndices)));
	m_resManager->addMaterial("FCMaterial", m_resManager->getShaderType().get("flatColour"), m_resManager->getVertexArrayType().get("FCcube"));
	m_FCstate = Engine::OscilateComponent::state::UP;
	m_TPstate = Engine::OscilateComponent::state::DOWN;

	//!Creates a i by j by k grid of flat cubes
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				m_materials.push_back(std::make_shared<Engine::MaterialComponent>(Engine::MaterialComponent(m_resManager->getMaterialType().get("FCMaterial"))));
				m_positions.push_back(std::make_shared<Engine::PositionComponent>(Engine::PositionComponent(glm::vec3(i * 3.f, j * 3.f, k * 3.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f))));
				m_velocities.push_back(std::make_shared<Engine::VelocityComponent>(Engine::VelocityComponent(glm::vec3(0.f), glm::vec3(0.f, 20.f, 0.0))));
				m_oscilation.push_back(std::make_shared<Engine::OscilateComponent>(Engine::OscilateComponent(m_FCstate, m_timeSummed)));


				m_gameObjects.push_back(std::make_shared<FlatCube>());
				m_gameObjects.back()->addComponent(m_materials.back());
				m_gameObjects.back()->addComponent(m_positions.back());
				m_gameObjects.back()->addComponent(m_velocities.back());
				m_gameObjects.back()->addComponent(m_oscilation.back());
			}
		}
	}

	m_resManager->addShader("postProcess", "assets/shaders/Framebuffer.glsl");
	m_renderer->setPPShader(m_resManager->getShaderType().get("postProcess"));

	//!tp cube res. manager code
	m_resManager->addShader("texturedPhong","assets/shaders/texturedPhongTess.glsl"); 
	m_resManager->addVertexArray("TPcube");
	m_resManager->getVertexArrayType().get("TPcube")->addVertexBuffer(m_resManager->addVertexBuffer("TPVBO", TPvertices, sizeof(TPvertices), m_resManager->getShaderType().get("texturedPhong")->getBufferLayout()));
	m_resManager->getVertexArrayType().get("TPcube")->addIndexBuffer(m_resManager->addIndexBuffer("TPIBO", CubeIndices, sizeof(CubeIndices)));
	m_resManager->addMaterial("TPMaterial", m_resManager->getShaderType().get("texturedPhong"), m_resManager->getVertexArrayType().get("TPcube"));

 	m_resManager->addTexture("letterCube","assets/textures/letterCube.png");
	m_resManager->addTexture("numberCube","assets/textures/numberCube.png");

	//!Creates a i by j by k grid of Textured cubes
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				m_materials.push_back(std::make_shared<Engine::MaterialComponent>(Engine::MaterialComponent(m_resManager->getMaterialType().get("TPMaterial"))));
				m_positions.push_back(std::make_shared<Engine::PositionComponent>(Engine::PositionComponent(glm::vec3(i * -3.f - 3, j * 3.f - 3, k * 3.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f))));
				m_velocities.push_back(std::make_shared<Engine::VelocityComponent>(Engine::VelocityComponent(glm::vec3(0.f), glm::vec3(0.f, 20.f, 0.0))));
				m_oscilation.push_back(std::make_shared<Engine::OscilateComponent>(Engine::OscilateComponent(m_TPstate, m_timeSummed)));

				m_gameObjects.push_back(std::make_shared<TPCube>());
				m_gameObjects.back()->addComponent(m_materials.back());
				m_gameObjects.back()->addComponent(m_positions.back());
				m_gameObjects.back()->addComponent(m_velocities.back());
				m_gameObjects.back()->addComponent(m_oscilation.back());
			}
		}
	}

	m_audioManager = Engine::Application::getInstance().getAudio();
	//! audio load sound
  
	m_audioManager->loadSound("assets/audio/sounds/drumloop.wav", true, true, false);
	//m_audioManager->playSound("assets/audio/sounds/drumloop.wav");

	for (auto& CGO : m_gameObjects) {
		CGO->onAttach();
	};

	//! Set Default Light Parameters
	m_LightPos = glm::vec3(0.f, 3.f, 10.f);
	m_LightColor = glm::vec3(1.f, 1.f, 1.f);
}

void GameLayer::onDetach()
{
}

void GameLayer::onUpdate(float timestep)
{
	//Sets Current Selected Object on a mouse click
	if (Engine::InputPoller::isMouseButtonPressed(MOUSE_BUTTON_LEFT) && m_Body != m_currentSelection)
	{
		m_currentSelection = m_Body;
		if (m_currentSelection != 0)
		{
			std::shared_ptr<Engine::GameObject> gameObject;
			std::shared_ptr<Engine::PositionComponent> positionComponent;

			for (int i = 0; i < m_gameObjects.size(); i++)
			{
				if (m_gameObjects[i]->getObjectID() == m_currentSelection)
				{
					gameObject = m_gameObjects[i];
					positionComponent = m_positions[i];
				}
			}

			//Gets transform values of selected component.
			m_Position = positionComponent->getPosition();
			m_Rotation = positionComponent->getRotation();
			m_Scale = positionComponent->getScale();
		}
		else 
		{
			m_Position = glm::vec3(0);
			m_Rotation = glm::vec3(0);
			m_Scale = glm::vec3(0);
		}
	}

	m_elapsedTime += timestep;
	m_Framerate = 1.0f / timestep;

	Engine::Renderer::SceneData data;
	data.ViewProjectionMatrix = m_camera->getCamera()->getViewProjection();


	//Clear window
	m_renderer->actionCommand(Engine::RenderCommand::setClearColourCommand(.8f, .8f, .8f, 1.0f));
	
	//Assign Framebufffer
	m_renderer->beginScene(data);

	m_renderer->actionCommand(Engine::RenderCommand::ClearDepthColourBufferCommand());

	m_renderer->actionCommand(Engine::RenderCommand::setDepthTestLessCommand(true));
	m_renderer->actionCommand(Engine::RenderCommand::setBackfaceCullingCommand(true));
	m_audioManager->update();

	glm::mat4 projection = m_camera->getCamera()->getProjection();
	glm::mat4 view = m_camera->getCamera()->getView();
	glm::mat4 FCtranslation, TPtranslation;

	glm::mat4 vp = projection * view;

	glm::vec3 lightPos = glm::vec3(0.f, 3.f, 10.f);
	glm::vec3 viewPos = m_camera->getPosition();
	glm::vec3 lightColour = glm::vec3(1.f, 1.f, 1.f);

	unsigned int texSlot = 0;
	int i = 0;

	//Render all game objects
	for (auto& CGO : m_gameObjects) {
		CGO->onUpdate(timestep);
		CGO->setViewProjection(vp);
		float id = CGO->getObjectIDfloat();
		m_materials[i]->getMaterial()->setDataElement("u_objectID", (void*)&id);
		m_materials[i]->getMaterial()->setDataElement("u_viewPos", (void*)&viewPos[0]);
		
		m_materials[i]->getMaterial()->setDataElement("u_lightPos", (void*)&m_LightPos[0]);
		m_materials[i]->getMaterial()->setDataElement("u_lightColour", (void*)&m_LightColor[0]);
		if (m_materials[i]->getMaterial() == m_resManager->getMaterialType().get("TPMaterial"))
		{
			if(m_TPstate == m_oscilation.back()->getState())
				m_resManager->getTextureType().get("numberCube")->bind(texSlot);
			else
				m_resManager->getTextureType().get("letterCube")->bind(texSlot);
			m_materials[i]->getMaterial()->setDataElement("u_texData", (void*)&texSlot);
		}

		m_renderer->submit(m_materials[i]->getMaterial());
		i++;
	};

	m_renderer->addPPFloat("u_time", &m_elapsedTime);

	//Render framebuffer
	m_renderer->flush();

	m_camera->onUpdate(timestep);

	m_renderer->actionCommand(Engine::RenderCommand::setDepthTestLessCommand(false));
	m_renderer->actionCommand(Engine::RenderCommand::setBackfaceCullingCommand(false));
}

void GameLayer::onEvent(Engine::Event & event)
{
	m_camera->onEvent(event);
	m_renderer->onEvent(event);

	Engine::EventDispatcher dispatcher(event);

	dispatcher.dispatch<Engine::MouseMovedEvent>(std::bind(&GameLayer::onMouseMoved, this, std::placeholders::_1));
}

bool GameLayer::onMouseMoved(Engine::MouseMovedEvent e)
{
	int oldBody = m_Body;
	int px = m_renderer->getObjectIDatPixel(e.getXOffset(),e.getYOffset());
	float pxCol = (float)px/ 255.f;

	if (m_gameObjects.size() != 0)
	m_Body = round(pxCol * m_gameObjects[0]->getObjectIDnum());

	if (m_Body != oldBody)
	NG_INFO("Body Hit: {0}", m_Body);

	return true;
}

bool GameLayer::onResize(Engine::WindowResizeEvent e)
{
	return false;
}

void GameLayer::onImGuiRender()
{
	std::string time = "Elapsed Time : " + std::to_string(m_elapsedTime);
	std::string framerate = "Framerate : " + std::to_string((int)m_Framerate);

	//!Displays Time and framerate
	ImGui::Text(time.c_str());
	ImGui::Text(framerate.c_str());

	//!Buttons to create cubes
	if (ImGui::Button("Create Flat Cube")) {
		createFlatCube();
	}
	if (ImGui::Button("Create Textured Cube")) {
		createTexturedCube();
	}

	//!If an object is selected
	if (m_currentSelection != 0)
	{
		std::shared_ptr<Engine::GameObject> gameObject;
		std::shared_ptr<Engine::PositionComponent> positionComponent;

		for (int i = 0; i < m_gameObjects.size(); i++)
		{
			if (m_gameObjects[i]->getObjectID() == m_currentSelection)
			{
				gameObject = m_gameObjects[i];
				positionComponent = m_positions[i];
			}
		}

		std::string curSelection = ("Object ID: " + std::to_string(m_currentSelection));
		if (ImGui::CollapsingHeader(curSelection.c_str()))
		{
			if (ImGui::CollapsingHeader("Transforms"))
			{
				//!Set Position
				if (ImGui::CollapsingHeader("Position"))
				{
					ImGui::InputFloat3("Position", &m_Position[0]);
					gameObject->sendMessage(Engine::ComponentMessage(Engine::ComponentMessageType::PositionSet, m_Position));
				}
				else
				{
					m_Position = positionComponent->getPosition();
				}
				//!Set Rotation
				if (ImGui::CollapsingHeader("Rotation"))
				{
					ImGui::InputFloat3("Rotation", &m_Rotation[0]);
					gameObject->sendMessage(Engine::ComponentMessage(Engine::ComponentMessageType::RotationSet, m_Rotation));
				}
				else
				{
					m_Rotation = positionComponent->getRotation();
				}
				//!Set Scale
				if (ImGui::CollapsingHeader("Scale"))
				{
					ImGui::InputFloat3("Scale", &m_Scale[0]);
					gameObject->sendMessage(Engine::ComponentMessage(Engine::ComponentMessageType::ScaleSet, m_Scale));
				}
				else 
				{
					m_Scale = positionComponent->getScale();
				}
			}
			//!Deletes the current object from the scene
			if (ImGui::Button("Delete Selection"))
			{
				for (int i = 0; i < m_gameObjects.size(); i++)
				{
					if (m_gameObjects[i]->getObjectID() == m_currentSelection)
					{
						m_gameObjects.erase(m_gameObjects.begin() + i);
						m_materials.erase(m_materials.begin() + i);
						m_positions.erase(m_positions.begin() + i);
						m_velocities.erase(m_velocities.begin() + i);
						m_oscilation.erase(m_oscilation.begin() + i);

						NG_INFO("GameObject(ID:{0}) removed", m_currentSelection);
						m_currentSelection = 0;
					}
				}
			}
		}
	}
	else
	{
		ImGui::Text("No Selection");
	}
	//!Light Properties 
	if (ImGui::CollapsingHeader("Light"))
	{
		ImGui::InputFloat3("Light Position", &m_LightPos[0]);
		ImGui::ColorPicker3("Light Color", &m_LightColor[0]);
	}
	ImGui::SliderFloat("Volume", &m_VolumeAudio, 0, 100);
	//!Removes all game objects from the scene
	if (ImGui::Button("Delete All Game Objects"))
	{
		m_gameObjects.resize(0);
		m_materials.resize(0);
		m_positions.resize(0);
		m_velocities.resize(0);
		m_oscilation.resize(0);
		m_currentSelection = 0;

		NG_INFO("All Game Objects Removed");
	}
	
}

void GameLayer::createFlatCube()
{
	m_materials.push_back(std::make_shared<Engine::MaterialComponent>(Engine::MaterialComponent(m_resManager->getMaterialType().get("FCMaterial"))));
	m_positions.push_back(std::make_shared<Engine::PositionComponent>(Engine::PositionComponent(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f))));
	m_velocities.push_back(std::make_shared<Engine::VelocityComponent>(Engine::VelocityComponent(glm::vec3(0.f), glm::vec3(0.f, 20.f, 0.0))));
	m_oscilation.push_back(std::make_shared<Engine::OscilateComponent>(Engine::OscilateComponent(m_FCstate, m_timeSummed)));


	m_gameObjects.push_back(std::make_shared<FlatCube>());
	m_gameObjects.back()->addComponent(m_materials.back());
	m_gameObjects.back()->addComponent(m_positions.back());
	m_gameObjects.back()->addComponent(m_velocities.back());
	m_gameObjects.back()->addComponent(m_oscilation.back());

	m_gameObjects.back()->onAttach();
}

void GameLayer::createTexturedCube()
{
	m_materials.push_back(std::make_shared<Engine::MaterialComponent>(Engine::MaterialComponent(m_resManager->getMaterialType().get("TPMaterial"))));
	m_positions.push_back(std::make_shared<Engine::PositionComponent>(Engine::PositionComponent(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f))));
	m_velocities.push_back(std::make_shared<Engine::VelocityComponent>(Engine::VelocityComponent(glm::vec3(0.f), glm::vec3(0.f, 20.f, 0.0))));
	m_oscilation.push_back(std::make_shared<Engine::OscilateComponent>(Engine::OscilateComponent(m_TPstate, m_timeSummed)));

	m_gameObjects.push_back(std::make_shared<TPCube>());
	m_gameObjects.back()->addComponent(m_materials.back());
	m_gameObjects.back()->addComponent(m_positions.back());
	m_gameObjects.back()->addComponent(m_velocities.back());
	m_gameObjects.back()->addComponent(m_oscilation.back());

	m_gameObjects.back()->onAttach();
}

//!Text Layer Definitions - not functioning

void TextLayer::onAttach()
{
	m_renderer = std::shared_ptr<Engine::Renderer>(Engine::Renderer::createBasicText2D());
	m_camera = std::shared_ptr<Engine::FreeOrthoCameraController2D>(new Engine::FreeOrthoCameraController2D());
	m_camera->init(0, 800, 0, 600);
	m_camera->setPosition(glm::vec3(0.f, 0.f, 0.f));

	m_Text.reset(Engine::Text::create("assets/fonts/Insanibc.ttf"));

	m_Shader.reset(Engine::Shader::create("assets/shaders/Text.glsl"));

	float vertices[6 * 4];

	m_Texture.reset(Engine::Texture::createFromFile("assets/textures/letterCube.png"));

	m_VBOText.reset(Engine::VertexBuffer::CreateDynamic(sizeof(vertices), m_Shader->getBufferLayout()));
	m_VAOText.reset(Engine::VertexArray::Create());
	m_VAOText->addVertexBuffer(m_VBOText);
	m_Material.reset(Engine::Material::create(m_Shader, m_VAOText));

	m_Text->setPosition(glm::vec2(0.0,0.0));
	m_Text->setColour(glm::vec3(1.0, 1.0, 1.0));
	m_Text->setScale(300);
	std::string text = "TEST STRING 123";
	m_Text->setText(text);
}

void TextLayer::onDetach()
{
}

void TextLayer::onUpdate(float timestep)
{
	m_camera->onUpdate(timestep);

	glm::mat4 projection = m_camera->getCamera()->getProjection();
	glm::mat4 view = m_camera->getCamera()->getView();

	glm::mat4 proj = glm::ortho(0.f, 800.f, 600.f, 0.0f, -1.0f, 1.0f);

	m_Material->setDataElement("u_projection", (void*)&projection[0][0]);
	m_Material->setDataElement("u_view", (void*)&view[0][0]);

	m_renderer->actionCommand(Engine::RenderCommand::setOneMinusAlphaBlending(true));

	m_Text->render(m_Material);

	m_renderer->actionCommand(Engine::RenderCommand::setOneMinusAlphaBlending(false));
}

void TextLayer::onEvent(Engine::Event & event)
{
}

void TextLayer::onImGuiRender()
{
}

//!Engine App Definitions

engineApp::engineApp()
{
	PushLayer(new GameLayer("GameLayer"));
	//PushLayer(new TextLayer("TextLayer"));
}

engineApp::~engineApp()
{
}

Engine::Application* Engine::startApplication()
{
	return new engineApp();
}