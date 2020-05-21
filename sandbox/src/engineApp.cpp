/** \file engineApp.cpp
*/
#include "engineApp.h"
#include "IMGui/IMGuiSystem.h"


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

	unsigned int indices[3 * 12] = {
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
	m_resManager->addShader("flatColour","assets/shaders/flatColour.glsl"); 
	m_resManager->addVertexArray("FCcube");
	m_resManager->getVertexArrayType().get("FCcube")->addVertexBuffer(m_resManager->addVertexBuffer("FCVBO", FCvertices, sizeof(FCvertices), m_resManager->getShaderType().get("flatColour")->getBufferLayout()));
	m_resManager->getVertexArrayType().get("FCcube")->addIndexBuffer(m_resManager->addIndexBuffer("FCIBO", indices, sizeof(indices)));
	m_resManager->addMaterial("FCMaterial", m_resManager->getShaderType().get("flatColour"), m_resManager->getVertexArrayType().get("FCcube"));

	m_resManager->addShader("postProcess", "assets/shaders/Framebuffer.glsl");
	m_renderer->setPPShader(m_resManager->getShaderType().get("postProcess"));

	//tp cube res. manager code
	m_resManager->addShader("texturedPhong","assets/shaders/texturedPhong.glsl"); 
	m_resManager->addVertexArray("TPcube");
	m_resManager->getVertexArrayType().get("TPcube")->addVertexBuffer(m_resManager->addVertexBuffer("TPVBO", TPvertices, sizeof(TPvertices), m_resManager->getShaderType().get("texturedPhong")->getBufferLayout()));
	m_resManager->getVertexArrayType().get("TPcube")->addIndexBuffer(m_resManager->addIndexBuffer("TPIBO", indices, sizeof(indices)));
	m_resManager->addMaterial("TPMaterial", m_resManager->getShaderType().get("texturedPhong"), m_resManager->getVertexArrayType().get("TPcube"));

 	m_resManager->addTexture("letterCube","assets/textures/letterCube.png");
	m_resManager->addTexture("numberCube","assets/textures/numberCube.png");

	m_FCmodel = glm::translate(glm::mat4(1), glm::vec3(1.5, 0, 3));
	m_TPmodel = glm::translate(glm::mat4(1), glm::vec3(-1.5, 0, 3));

	m_audioManager = Engine::Application::getInstance().getAudio();
	// audio load sound
	m_audioManager->loadSound("assets/audio/sounds/drumloop.wav", true, true, false);
	m_audioManager->playSound("assets/audio/sounds/drumloop.wav");
	
}

void GameLayer::onDetach()
{
}

void GameLayer::onUpdate(float timestep)
{
	Engine::Renderer::SceneData data;
	data.ViewProjectionMatrix = m_camera->getCamera()->getViewProjection();
	m_renderer->beginScene(data);

	m_renderer->actionCommand(Engine::RenderCommand::setDepthTestLessCommand(true));
	m_renderer->actionCommand(Engine::RenderCommand::setBackfaceCullingCommand(true));
	m_audioManager->update();
  
	m_renderer->actionCommand(Engine::RenderCommand::setClearColourCommand(.8f, .8f, .8f, 1.0f));
	m_renderer->actionCommand(Engine::RenderCommand::ClearDepthColourBufferCommand());

	glm::mat4 projection = m_camera->getCamera()->getProjection();
	glm::mat4 view = m_camera->getCamera()->getView();
	glm::mat4 FCtranslation, TPtranslation;

	if (m_goingUp)
	{
	FCtranslation = glm::translate(m_FCmodel, glm::vec3(0.0f, 0.2f * timestep, 0.0f));
	TPtranslation = glm::translate(m_TPmodel, glm::vec3(0.0f, -0.2f * timestep, 0.0f));
	}
	else
	{
	FCtranslation = glm::translate(m_FCmodel, glm::vec3(0.0f, -0.2f * timestep, 0.0f));
	TPtranslation = glm::translate(m_TPmodel, glm::vec3(0.0f, 0.2f * timestep, 0.0f));
	}

	m_timeSummed += timestep;
	if (m_timeSummed > 20.0f) {
	m_timeSummed = 0.f;
	m_goingUp = !m_goingUp;
	}


	m_FCmodel = glm::rotate(FCtranslation, glm::radians(20.f) * timestep, glm::vec3(0.f, 1.f, 0.f)); // Spin the cube at 20 degrees per second
	m_TPmodel = glm::rotate(TPtranslation, glm::radians(-20.f) * timestep, glm::vec3(0.f, 1.f, 0.f)); // Spin the cube at 20 degrees per second

	// End of code to make the cube move.
	glm::mat4 fcMVP = projection * view * m_FCmodel;

	m_resManager->getMaterialType().get("FCMaterial")->setDataElement("u_MVP", (void*)&fcMVP[0][0]);

	m_renderer->submit(m_resManager->getMaterialType().get("FCMaterial"));

	glm::mat4 tpMVP = projection * view * m_TPmodel;
	unsigned int texSlot = 0;
	if (m_goingUp) 
	{
		m_resManager->getTextureType().get("letterCube")->bind(texSlot);
	}
	else 
	{
		m_resManager->getTextureType().get("numberCube")->bind(texSlot);
	}

	m_resManager->getMaterialType().get("TPMaterial")->setDataElement("u_MVP", (void *)&tpMVP[0][0]);
	m_resManager->getMaterialType().get("TPMaterial")->setDataElement("u_model", (void *)&m_TPmodel[0][0]);

	glm::vec3 lightPos = glm::vec3(0.f, 3.f, 10.f);
	glm::vec3 viewPos = m_camera->getPosition();
	glm::vec3 lightColour = glm::vec3(1.f, 1.f, 1.f);

	m_resManager->getMaterialType().get("TPMaterial")->setDataElement("u_lightPos", (void*)&lightPos[0]);
	m_resManager->getMaterialType().get("TPMaterial")->setDataElement("u_viewPos", (void*)&viewPos[0]);
	m_resManager->getMaterialType().get("TPMaterial")->setDataElement("u_lightColour", (void*)&lightColour[0]);
	m_resManager->getMaterialType().get("TPMaterial")->setDataElement("u_texData", (void*)&texSlot);

	m_renderer->submit(m_resManager->getMaterialType().get("TPMaterial"));

	m_renderer->actionCommand(Engine::RenderCommand::setClearColourCommand(.0f, .0f, .0f, 1.0f));
	m_renderer->actionCommand(Engine::RenderCommand::ClearDepthColourBufferCommand());

	m_renderer->flush();

	m_camera->onUpdate(timestep);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Demo window");
	ImGui::Button("Hello!");
	ImGui::End();

	ImGuiIO& io = ImGui::GetIO();
	glm::vec2 res = glm::vec2(800, 600);
	io.DisplaySize = ImVec2((float)res.x, (float)res.y);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GameLayer::onEvent(Engine::Event & event)
{
}

void TextLayer::onAttach()
{
	m_renderer = std::shared_ptr<Engine::Renderer>(Engine::Renderer::createBasicText2D());
	m_camera = std::shared_ptr<Engine::FreeOrthoCameraController2D>(new Engine::FreeOrthoCameraController2D());

	m_Text.reset(Engine::Text::create("assets/fonts/TestFont.ttf"));

	m_camera->init(0, 800, 0, 600);
	m_camera->setPosition(glm::vec3(0.f, 0.f, 0.f));
	//m_camera->init(0,0,800,600);

	m_Shader.reset(Engine::Shader::create("assets/shaders/Text.glsl"));

	float vertices[6 * 4];
	unsigned int indicies[6 * 4];

	float verticesTexture[4 * 4] = {
		0.f, 0.f, 0.f, 1.0f,
		0.f, 150.f, 0.f, 0.f,
		266.f, 150.f, 1.0f, 0.0f,
		266.f, 0.f, 1.0f, 1.0f
	};
	unsigned int indiciesTexture[4] = { 0, 1, 2, 3 };

	m_Texture.reset(Engine::Texture::createFromFile("assets/textures/letterCube.png"));

	//m_indexBuffer.reset(Engine::IndexBuffer::Create(indicies, sizeof(indicies)));
	m_VBOText.reset(Engine::VertexBuffer::CreateDynamic(sizeof(vertices), m_Shader->getBufferLayout()));
	m_VAOText.reset(Engine::VertexArray::Create());
	//m_VAO->addIndexBuffer(m_indexBuffer);
	m_VAOText->addVertexBuffer(m_VBOText);
	m_Material.reset(Engine::Material::create(m_Shader, m_VAOText));

	m_VAO.reset(Engine::VertexArray::Create());
	m_VBO.reset(Engine::VertexBuffer::Create(verticesTexture, sizeof(verticesTexture), m_Shader->getBufferLayout()));
	m_indexBuffer.reset(Engine::IndexBuffer::Create(indiciesTexture, sizeof(indiciesTexture)));
	m_VAO->addIndexBuffer(m_indexBuffer);
	m_VAO->addVertexBuffer(m_VBO);

	m_Material2.reset(Engine::Material::create(m_Shader, m_VAO));

	m_Text->setPosition(glm::vec2(0.0,0.0));
	m_Text->setColour(glm::vec3(1.0, 1.0, 1.0));
	m_Text->setScale(1);
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

	m_Material->setDataElement("u_projection", (void*)&projection[0][0]);
	//m_Material2->setDataElement("u_projection", (void*)&projection[0][0]);

	unsigned int slot = 0;

	m_Texture->bind(slot);

	//m_Material2->setDataElement("u_texData", (void*)&slot);
	//m_renderer->submit(m_Material2);
	m_Text->render(m_Material);
}

void TextLayer::onEvent(Engine::Event & event)
{
}

engineApp::engineApp()
{
	PushLayer(new GameLayer("GameLayer"));
	PushLayer(new TextLayer("TextLayer"));
}

engineApp::~engineApp()
{
}


Engine::Application* Engine::startApplication()
{
	return new engineApp();
}