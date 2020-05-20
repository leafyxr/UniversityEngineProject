#include "engine_pch.h"
#include "GLFW\GLRenderer.h"
#include "glad\glad.h"

namespace Engine {

	void GLSuperSimpleRenderer::actionCommand(RenderCommand * command)
	{
		command->action();
		delete command;
	}

	void GLSuperSimpleRenderer::submit(const std::shared_ptr<Material>& material)
	{
		auto shader = material->getShader();
		shader->bind();

		auto geometry = std::get<std::shared_ptr<VertexArray>>(material->getGeometry());
		geometry->Bind();

		auto uniformData = material->getData();
		for (auto dataPair : uniformData) {
			shader->uploadData(dataPair.first, dataPair.second);
		}

		//glDrawElements(GL_TRIANGLES, geometry->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
		//glDrawArrays(GL_PATCHES, geometry->getIndexBuffer()->getCount(), GL_UNSIGNED_INT);
		//glDrawElements();
		glDrawArrays(GL_PATCHES, 0, geometry->getIndexBuffer()->getCount());
	}
	void GLClearDepthColourBufferCommand::action()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void GLSetClearColourCommand::action()
	{
		glClearColor(m_r, m_g, m_b, m_a);
	}
	void GLsetDepthTestLessCommand::action()
	{
		if (m_enabled) {
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
		}
		else {
			glDisable(GL_DEPTH_TEST);
			glDepthFunc(GL_NONE);
		}
	}
	void GLsetBackfaceCullingCommand::action()
	{
		if (m_enabled) {	//???
			//glEnable(GL_CULL_FACE);
			//glCullFace(GL_BACK);
		}
		else {
			glDisable(GL_CULL_FACE);
			glCullFace(GL_NONE);
		}
	}
}