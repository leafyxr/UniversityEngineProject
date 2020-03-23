#include "engine_pch.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GLFW/GLText.h"
#include "systems/log.h"



namespace Engine {


	void GLTextRenderer::actionCommand(RenderCommand * command)
	{
		command->action();
		delete command;
	}

	void GLTextRenderer::submit(const std::shared_ptr<Material>& material)
	{
		auto shader = material->getShader();
		shader->bind();

		auto geometry = std::get<std::shared_ptr<VertexArray>>(material->getGeometry());
		geometry->Bind();

		auto uniformData = material->getData();
		for (auto dataPair : uniformData) {
			shader->uploadData(dataPair.first, dataPair.second);
		}

		glDrawElements(GL_QUADS, geometry->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
	}

	GLText::GLText(const std::string & path)
	{
		FT_Library ft;
		if (FT_Init_FreeType(&ft)) {
			NG_ERROR("Freetype: Could not initialise Library");
		}
		FT_Face face;
		if (FT_New_Face(ft, path.c_str(), 0, &face)) {
			NG_ERROR("Freetype: Could not load font");
		}

		FT_Set_Pixel_Sizes(face, 0, 48);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		for (GLubyte c = 0; c < 128; c++) {
			if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
				NG_ERROR("Freetype: Could not load Glyph");
				continue;
			}
			m_Tex.reset(Texture::createFromRawData(
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				1,
				face->glyph->bitmap.buffer));
			Character ch = {
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				glm::vec2(0.0f),
				glm::vec2(1.0f),
				face->glyph->advance.x 
			};
			m_characters.insert(std::pair<char, Character>(c, ch));
		}
		FT_Done_Face(face);
		FT_Done_FreeType(ft);
	}
	void GLText::render(std::shared_ptr<Material> mat)
	{
	}
}