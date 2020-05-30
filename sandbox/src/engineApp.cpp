/** \file engineApp.cpp
*/
#include "engineApp.h"
#include "IMGui.h"

#include "flatCube.h"
#include "texturedPhongCube.h"

#include "systems/InputPoller.h"

void GameLayer::onAttach()
{
	m_renderer = std::shared_ptr<Engine::Renderer>(Engine::Renderer::createPostProcess3D());
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
	//fc cube res. manager code
	m_resManager->addShader("flatColour","assets/shaders/flatColourTess.glsl"); 
	m_resManager->addVertexArray("FCcube");
	m_resManager->getVertexArrayType().get("FCcube")->addVertexBuffer(m_resManager->addVertexBuffer("FCVBO", FCvertices, sizeof(FCvertices), m_resManager->getShaderType().get("flatColour")->getBufferLayout()));
	m_resManager->getVertexArrayType().get("FCcube")->addIndexBuffer(m_resManager->addIndexBuffer("FCIBO", CubeIndices, sizeof(CubeIndices)));
	m_resManager->addMaterial("FCMaterial", m_resManager->getShaderType().get("flatColour"), m_resManager->getVertexArrayType().get("FCcube"));
	m_FCstate = Engine::OscilateComponent::state::UP;
	m_TPstate = Engine::OscilateComponent::state::DOWN;


	

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

	//tp cube res. manager code
	m_resManager->addShader("texturedPhong","assets/shaders/texturedPhongTess.glsl"); 
	m_resManager->addVertexArray("TPcube");
	m_resManager->getVertexArrayType().get("TPcube")->addVertexBuffer(m_resManager->addVertexBuffer("TPVBO", TPvertices, sizeof(TPvertices), m_resManager->getShaderType().get("texturedPhong")->getBufferLayout()));
	m_resManager->getVertexArrayType().get("TPcube")->addIndexBuffer(m_resManager->addIndexBuffer("TPIBO", CubeIndices, sizeof(CubeIndices)));
	m_resManager->addMaterial("TPMaterial", m_resManager->getShaderType().get("texturedPhong"), m_resManager->getVertexArrayType().get("TPcube"));

 	m_resManager->addTexture("letterCube","assets/textures/letterCube.png");
	m_resManager->addTexture("numberCube","assets/textures/numberCube.png");
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
	// audio load sound
  
	m_audioManager->loadSound("assets/audio/sounds/drumloop.wav", true, true, false);
	//m_audioManager->playSound("assets/audio/sounds/drumloop.wav");


	m_Text.reset(Engine::Text::create("assets/fonts/Insanibc.ttf"));

	m_Shader.reset(Engine::Shader::create("assets/shaders/Text.glsl"));

	float vertices[6 * 4];

	m_Texture.reset(Engine::Texture::createFromFile("assets/textures/letterCube.png"));

	m_VBOText.reset(Engine::VertexBuffer::CreateDynamic(sizeof(vertices), m_Shader->getBufferLayout()));
	m_VAOText.reset(Engine::VertexArray::Create());
	m_VAOText->addVertexBuffer(m_VBOText);
	m_Material.reset(Engine::Material::create(m_Shader, m_VAOText));

	m_Text->setPosition(glm::vec2(0.0, 0.0));
	m_Text->setColour(glm::vec3(1.0, 1.0, 1.0));
	m_Text->setScale(10);
	std::string text = "TEST STRING 123";
	m_Text->setText(text);


	for (auto& CGO : m_gameObjects) {
		CGO->onAttach();
	};
}

void GameLayer::onDetach()
{
}

void GameLayer::onUpdate(float timestep)
{
	if (Engine::InputPoller::isMouseButtonPressed(MOUSE_BUTTON_LEFT) && m_Body != m_currentSelection)
	{
		m_currentSelection = m_Body;
		if (m_currentSelection != 0)
		{
			std::shared_ptr<Engine::GameObject> gameObject = m_gameObjects[m_currentSelection - 1];
			std::shared_ptr<Engine::PositionComponent> positionComponent = m_positions[m_currentSelection - 1];

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

	Engine::Renderer::SceneData data;
	data.ViewProjectionMatrix = m_camera->getCamera()->getViewProjection();

	m_renderer->actionCommand(Engine::RenderCommand::setClearColourCommand(.8f, .8f, .8f, 1.0f));
	
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
	for (auto& CGO : m_gameObjects) {
		CGO->onUpdate(timestep);
		CGO->setViewProjection(vp);
		float id = CGO->getObjectIDfloat();
		m_materials[i]->getMaterial()->setDataElement("u_objectID", (void*)&id);
		m_materials[i]->getMaterial()->setDataElement("u_viewPos", (void*)&viewPos[0]);
		if (m_materials[i]->getMaterial() == m_resManager->getMaterialType().get("TPMaterial"))
		{
		m_materials[i]->getMaterial()->setDataElement("u_lightPos", (void*)&lightPos[0]);
		m_materials[i]->getMaterial()->setDataElement("u_lightColour", (void*)&lightColour[0]);
			if(m_TPstate == m_oscilation.back()->getState())
				m_resManager->getTextureType().get("numberCube")->bind(texSlot);
			else
				m_resManager->getTextureType().get("letterCube")->bind(texSlot);
			m_materials[i]->getMaterial()->setDataElement("u_texData", (void*)&texSlot);
		}

		m_renderer->submit(m_materials[i]->getMaterial());
		i++;
	};

	m_renderer->actionCommand(Engine::RenderCommand::setOneMinusAlphaBlending(true));

	//m_Text->render(m_Material);

	m_renderer->actionCommand(Engine::RenderCommand::setOneMinusAlphaBlending(false));

	//NG_INFO("Time: {0}", m_elapsedTime);
	m_renderer->addPPFloat("u_time", &m_elapsedTime);

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
	m_Body = round(pxCol * m_gameObjects[0]->getObjectIDnum());

	if (m_Body != oldBody)
	NG_INFO("Body Hit: {0}", m_Body);

	return true;
}

bool GameLayer::onResize(Engine::WindowResizeEvent)
{
	return false;
}

void GameLayer::onImGuiRender()
{
	if (ImGui::Button("Create Flat Cube")) {
		createFlatCube();
	}
	if (ImGui::Button("Create Textured Cube")) {
		createTexturedCube();
	}
	if (m_currentSelection != 0)
	{
		std::shared_ptr<Engine::GameObject> gameObject = m_gameObjects[m_currentSelection - 1];
		std::shared_ptr<Engine::PositionComponent> positionComponent = m_positions[m_currentSelection - 1];

		std::string curSelection = ("Object ID: " + std::to_string(m_currentSelection));
		ImGui::Text(curSelection.c_str());
		if (ImGui::CollapsingHeader("Transforms")) 
		{
			if (ImGui::CollapsingHeader("Position"))
			{
				ImGui::InputFloat3("", &m_Position[0]);
			}
			if (ImGui::CollapsingHeader("Rotation"))
			{
				ImGui::InputFloat3("", &m_Rotation[0]);
			}
			if (ImGui::CollapsingHeader("Scale"))
			{
				ImGui::InputFloat3("", &m_Scale[0]);
			}
		}
		gameObject->sendMessage(Engine::ComponentMessage(Engine::ComponentMessageType::PositionSet, m_Position));
		gameObject->sendMessage(Engine::ComponentMessage(Engine::ComponentMessageType::RotationSet, m_Rotation));
		gameObject->sendMessage(Engine::ComponentMessage(Engine::ComponentMessageType::ScaleSet, m_Scale));

	}
	else
	{
		ImGui::Text("No Selection");
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
	throw std::logic_error("The method or operation is not implemented.");
}

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