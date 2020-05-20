#include "engine_pch.h"
#include "GLFW/GLPostProcessRenderer.h"
#include "glad\glad.h"
#include "GLFW\glfw3.h"
#include "Renderer/Buffer.h"
#include "systems/log.h"

namespace Engine 
{

	void GLPostProcessRenderer::actionCommand(RenderCommand* command)
	{
		command->action();
		delete command;
	}

	void GLPostProcessRenderer::beginScene(const SceneData& sceneData)
	{
		setFBOcolour();
	}

	void GLPostProcessRenderer::endScene()
	{

	}

	void GLPostProcessRenderer::submit(const std::shared_ptr<Material>& material)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferID);
		actionCommand(RenderCommand::setDepthTestLessCommand(true));

		auto shader = material->getShader();
		shader->bind();

		auto geometry = std::get<std::shared_ptr<VertexArray>>(material->getGeometry());
		geometry->Bind();

		auto uniformData = material->getData();
		for (auto dataPair : uniformData) {
			shader->uploadData(dataPair.first, dataPair.second);
		}

		glDrawElements(GL_TRIANGLES, geometry->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
	}

	void GLPostProcessRenderer::flush()
	{
		actionCommand(RenderCommand::setDepthTestLessCommand(false));
		m_ppShader->bind();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glActiveTexture(m_colourTextureUnit);
		glBindTexture(GL_TEXTURE_2D, m_colourTexture);
		m_ppShader->uploadData("u_texData", (void*)&m_colourTextureUnit);
		renderQuad();
	}

	void GLPostProcessRenderer::addPPUniform(const std::string& name, void* data)
	{
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

		NG_INFO("DIMENSIONS = {0} X {1}", SCR_WIDTH, SCR_HEIGHT);

		//Create Buffer
		glGenFramebuffers(1, &m_framebufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_colourTexture);

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

		//Create rbo
		unsigned int rbo;
		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
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
		}
		m_screenQuadVAO->Bind();
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);
	}

}