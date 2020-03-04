#include "engine_pch.h"
#include "GLFW/GLText.h"



namespace Engine {


	void GLTextRenderer::actionCommand(RenderCommand * command)
	{
	}
	void GLTextRenderer::submit(const std::shared_ptr<Material>& material)
	{
	}

	FT_Library GLText::s_ft;

	GLText::GLText(const std::string & path)
	{

	}
	void GLText::render(std::shared_ptr<Material> mat)
	{
	}
}