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
			unsigned int texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);
			/*
			m_Tex.reset(Texture::createFromRawData(
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				1,
				face->glyph->bitmap.buffer));
				*/
			//unsigned int* id = (unsigned int*)(m_Tex->getID());

			Character ch(
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				glm::vec2(0.0f),
				glm::vec2(1.0f),
				face->glyph->advance.x 
			);
			m_characters.insert(std::pair<char, Character>(c, ch));
		}
		FT_Done_Face(face);
		FT_Done_FreeType(ft);
		NG_INFO("Font Loaded from : {0}", path);
	}
	void GLText::render(std::shared_ptr<Material> mat)
	{
		mat->getShader()->bind();
		mat->setDataElement("u_fontColour", (void*)&m_Colour[0]);
		std::shared_ptr<VertexArray> VAO = std::get<std::shared_ptr<VertexArray>>(mat->getGeometry());
		VAO->Bind();
		float x = m_posX;
		float y = m_posY;

		std::string::const_iterator c;
		for (c = m_text.begin(); c != m_text.end(); c++) {
			Character Char = m_characters[*c];

			float xpos = x + Char.getBearing().x * m_Scale;
			float ypos = y + Char.getBearing().y * m_Scale;

			float width = Char.getSize().x * m_Scale;
			float height = Char.getSize().y * m_Scale;

			float vertices[6][4] = {
				{xpos, ypos + height, 0.0, 0.0},
				{xpos, ypos, 0.0, 1.0},
				{xpos + width, ypos, 1.0, 1.0},

				{xpos, ypos + height, 0.0, 0.0},
				{xpos + width, ypos, 1.0, 1.0},
				{xpos + width, ypos + height, 1.0, 0.0},
			};
			VAO->getVertexBuffer()[0]->Edit(*vertices, sizeof(vertices), 0);
			VAO->Bind();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, Char.getTexture());
			glDrawArrays(GL_TRIANGLES, 0, 6);
			x += (Char.getAdvance() >> 6) * m_Scale;
		}

	}
}