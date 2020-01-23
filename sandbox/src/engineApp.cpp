/** \file engineApp.cpp
*/
#include "engineApp.h"

void GameLayer::onAttach()
{
	m_renderer = std::shared_ptr<Engine::Renderer>(Engine::Renderer::createBasic3D());
	m_camera = std::shared_ptr<Engine::FPSCameraControllerEuler>(new Engine::FPSCameraControllerEuler());

	m_camera->init(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	m_camera->setPosition(glm::vec3(0.f, 0.f, 10.f));

	m_renderer->actionCommand(Engine::RenderCommand::setDepthTestLessCommand(true));
	m_renderer->actionCommand(Engine::RenderCommand::setBackfaceCullingCommand(true));

	m_FCvertexArray.reset(Engine::VertexArray::Create());
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
	m_FCvertexBuffer.reset(Engine::VertexBuffer::Create(FCvertices, sizeof(FCvertices)));
	m_FCprogram.reset(Engine::Shader::create("assets/shaders/flatColour.glsl"));
	m_FCvertexBuffer->setLayout(m_FCprogram->getBufferLayout());
	m_FCvertexArray->addVertexBuffer(m_FCvertexBuffer);
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
	m_FCindexBuffer.reset(Engine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));
	m_FCvertexArray->addIndexBuffer(m_FCindexBuffer);


	m_TPvertexArray.reset(Engine::VertexArray::Create());
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
	m_TPvertexBuffer.reset(Engine::VertexBuffer::Create(TPvertices, sizeof(TPvertices)));
	m_TPprogram.reset(Engine::Shader::create("assets/shaders/texturedPhong.glsl"));
	m_TPvertexBuffer->setLayout(m_TPprogram->getBufferLayout());
	m_TPvertexArray->addVertexBuffer(m_TPvertexBuffer);
	m_TPindexBuffer.reset(Engine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));
	m_TPvertexArray->addIndexBuffer(m_TPindexBuffer);
	m_letterTexture.reset(Engine::Texture::createFromFile("assets/textures/letterCube.png"));
	m_numberTexture.reset(Engine::Texture::createFromFile("assets/textures/numberCube.png"));
	m_FCmodel = glm::translate(glm::mat4(1), glm::vec3(1.5, 0, 3));
	m_TPmodel = glm::translate(glm::mat4(1), glm::vec3(-1.5, 0, 3));
	m_FCmaterial.reset(Engine::Material::create(m_FCprogram, m_FCvertexArray));
	m_TPmaterial.reset(Engine::Material::create(m_TPprogram, m_TPvertexArray));
}

void GameLayer::onDetach()
{
}

void GameLayer::onUpdate(float timestep)
{
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

	m_FCmaterial->setDataElement("u_MVP", (void*)&fcMVP[0][0]);

	m_renderer->submit(m_FCmaterial);

	glm::mat4 tpMVP = projection * view * m_TPmodel;
	unsigned int texSlot;
	if (m_goingUp) texSlot = m_letterTexture->getSlot();
	else texSlot = m_numberTexture->getSlot();

	m_TPmaterial->setDataElement("u_MVP", (void *)&tpMVP[0][0]);
	m_TPmaterial->setDataElement("u_model", (void *)&m_TPmodel[0][0]);

	glm::vec3 lightPos = glm::vec3(0.f, 3.f, 10.f);
	glm::vec3 viewPos = m_camera->getPosition();
	glm::vec3 lightColour = glm::vec3(1.f, 1.f, 1.f);

	m_TPmaterial->setDataElement("u_lightPos", (void*)&lightPos[0]);
	m_TPmaterial->setDataElement("u_viewPos", (void*)&viewPos[0]);
	m_TPmaterial->setDataElement("u_lightColour", (void*)&lightColour[0]);
	m_TPmaterial->setDataElement("u_texData", (void*)&texSlot);

	m_renderer->submit(m_TPmaterial);
	m_camera->onUpdate(timestep);
}

void GameLayer::onEvent(Engine::Event & event)
{
}

void UILayer::onAttach()
{
}

void UILayer::onDetach()
{
}

void UILayer::onUpdate(float timestep)
{
}

void UILayer::onEvent(Engine::Event & event)
{
}

engineApp::engineApp()
{
	PushLayer(new GameLayer("GameLayer"));
}

engineApp::~engineApp()
{
}


Engine::Application* Engine::startApplication()
{
	return new engineApp();
}