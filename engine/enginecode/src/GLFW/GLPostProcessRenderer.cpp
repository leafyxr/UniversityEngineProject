#include "engine_pch.h"
#include "GLFW/GLPostProcessRenderer.h"
#include "glad\glad.h"
#include "GLFW\glfw3.h"
#include "Renderer/Buffer.h"
#include "systems/log.h"
#include "systems/InputPoller.h"

namespace Engine 
{

	void GLPostProcessRenderer::actionCommand(RenderCommand* command)
	{
		command->action();
		delete command;
	}

	void GLPostProcessRenderer::beginScene(const SceneData& sceneData)
	{
		if (!m_Active)
		{
			NG_INFO("Generate Framebufer");
			setFBOcolour();
			m_Active = true;
		}
		glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferID);

		glDrawBuffer(GL_COLOR_ATTACHMENT1);
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		GLenum drawbuffers[]{ GL_COLOR_ATTACHMENT0 , GL_COLOR_ATTACHMENT1 };

		glDrawBuffers(2, drawbuffers);
	}

	void GLPostProcessRenderer::endScene()
	{

	}

	void GLPostProcessRenderer::submit(const std::shared_ptr<Material>& material)
	{
		actionCommand(RenderCommand::setDepthTestLessCommand(true));

		auto shader = material->getShader();
		shader->bind();

		auto geometry = std::get<std::shared_ptr<VertexArray>>(material->getGeometry());
		geometry->Bind();

		auto uniformData = material->getData();
		for (auto dataPair : uniformData) {
			shader->uploadData(dataPair.first, dataPair.second);
		}

		if (InputPoller::isKeyPressed(KEY_K)) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		if (shader->isTesselated()) glDrawElements(GL_PATCHES, geometry->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
		else glDrawElements(GL_TRIANGLES, geometry->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
	}

	void GLPostProcessRenderer::flush()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		actionCommand(RenderCommand::setDepthTestLessCommand(false));
		m_ppShader->bind();
		actionCommand(Engine::RenderCommand::setClearColourCommand(.5f, .5f, .5f, 1.0f));
		actionCommand(Engine::RenderCommand::ClearDepthColourBufferCommand());
		glActiveTexture(m_colourTextureUnit);
		glBindTexture(GL_TEXTURE_2D, m_colourTexture);
		m_ppShader->uploadData("u_texData", (void*)&m_colourTextureUnit);
		renderQuad();
	}

	void GLPostProcessRenderer::addPPUniform(const std::string& name, void* data)
	{
		m_ppShader->bind();
		m_ppShader->uploadData(name, data);
	}

	void GLPostProcessRenderer::deletePPUniform(const std::string& name)
	{
		throw std::logic_error("The method is not implemented.");
	}

	void GLPostProcessRenderer::setFBOdepth()
	{
		GLint m_viewport[4];
		glGetIntegerv(GL_VIEWPORT, m_viewport);

		//Create Buffer
		glGenFramebuffers(1, &m_framebufferID);
		glGenTextures(1, &m_depthTexture);
		//Create Texture
		glBindTexture(GL_TEXTURE_2D, m_depthTexture);
		//Texture Properties
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_viewport[2], m_viewport[3], 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
		//Bind image to fbo
		glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferID);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void GLPostProcessRenderer::setFBOcolour()
	{
		GLint m_viewport[4];
		glGetIntegerv(GL_VIEWPORT, m_viewport);

		int SCR_WIDTH = m_viewport[2];
		int SCR_HEIGHT = m_viewport[3];

		//Create Buffer
		glGenFramebuffers(1, &m_framebufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferID);

		//Create Texture
		glGenTextures(1, &m_colourTexture);
		glBindTexture(GL_TEXTURE_2D, m_colourTexture);
		//Texture Properties
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//Bind image to fbo
		glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferID);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colourTexture, 0);

		glBindFramebuffer(GL_FRAMEBUFFER, m_colourTexture);

		//Create Texture
		glGenTextures(1, &m_ObjectIDs);
		glBindTexture(GL_TEXTURE_2D, m_ObjectIDs);
		//Texture Properties
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//Bind image to fbo
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_ObjectIDs, 0);
		GLenum drawbuffers[]{ GL_COLOR_ATTACHMENT0 , GL_COLOR_ATTACHMENT1 };

		glDrawBuffers(2, drawbuffers);
	}

	void GLPostProcessRenderer::renderQuad()
	{
		if (m_screenQuadVAO == nullptr)
		{
			float quadVertices[] = {
				// positions        // texture Coords
				-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
				-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
				 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
				 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			};

			m_screenQuadVAO.reset(VertexArray::Create());

			std::shared_ptr<VertexBuffer> vbo;
			vbo.reset(VertexBuffer::Create(quadVertices, sizeof(quadVertices), m_ppShader->getBufferLayout()));

			unsigned int quadIndicies[] = {
				0, 1, 2 , 3, 2, 1
			};

			std::shared_ptr<IndexBuffer> ibo;
			ibo.reset(IndexBuffer::Create(quadIndicies, sizeof(quadIndicies)));

			m_screenQuadVAO->addVertexBuffer(vbo);
			m_screenQuadVAO->addIndexBuffer(ibo);
		}
		m_screenQuadVAO->Bind();
		//glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		if (InputPoller::isKeyPressed(KEY_L)) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glDrawElements(GL_TRIANGLES, m_screenQuadVAO->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
	}

	void GLPostProcessRenderer::addPPFloat(const std::string& name, float* data)
	{
		m_ppShader->bind();
		m_ppShader->uploadFloat(name, *data);
	}

	void GLPostProcessRenderer::addPPInt(const std::string& name, int* data)
	{
		m_ppShader->bind();
		m_ppShader->uploadInt(name, *data);
	}

	float GLPostProcessRenderer::getObjectIDatPixel(int x, int y)
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_framebufferID);
		glReadBuffer(GL_COLOR_ATTACHMENT1);

		GLint m_viewport[4];
		glGetIntegerv(GL_VIEWPORT, m_viewport);

		unsigned char pixel[3] = { 0 };
		glReadPixels(x, m_viewport[3] - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

		return (int)pixel[0];
	}

	void GLPostProcessRenderer::onEvent(Event& e)
	{
		Engine::EventDispatcher dispatcher(e);

		dispatcher.dispatch<Engine::WindowResizeEvent>(std::bind(&GLPostProcessRenderer::onResize, this, std::placeholders::_1));
	}

	bool GLPostProcessRenderer::onResize(WindowResizeEvent& e)
	{
		int SCR_WIDTH = e.getWidth();
		int SCR_HEIGHT = e.getHeight();

		//Create Buffer
		glDeleteFramebuffers(1, &m_framebufferID);
		glGenFramebuffers(1, &m_framebufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferID);

		//Create Texture
		glDeleteTextures(1, &m_colourTexture);
		glGenTextures(1, &m_colourTexture);
		glBindTexture(GL_TEXTURE_2D, m_colourTexture);
		//Texture Properties
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//Bind image to fbo
		glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferID);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colourTexture, 0);

		glBindFramebuffer(GL_FRAMEBUFFER, m_colourTexture);

		//Create Texture
		glDeleteTextures(1, &m_ObjectIDs);
		glGenTextures(1, &m_ObjectIDs);
		glBindTexture(GL_TEXTURE_2D, m_ObjectIDs);
		//Texture Properties
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//Bind image to fbo
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_ObjectIDs, 0);
		GLenum drawbuffers[]{ GL_COLOR_ATTACHMENT0 , GL_COLOR_ATTACHMENT1 };

		glDrawBuffers(2, drawbuffers);
		return false;
	}

}