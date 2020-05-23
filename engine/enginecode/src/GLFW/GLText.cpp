#include "engine_pch.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GLFW/GLText.h"
#include "systems/log.h"
#include "glm/gtc/matrix_transform.hpp"



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

	void GLTextRenderer::setPPShader(std::shared_ptr<Shader> shader)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void GLTextRenderer::addPPUniform(const std::string& name, void* data)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void GLTextRenderer::deletePPUniform(const std::string& name)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	const int& GLTextRenderer::getColourTextureUnit()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	const int& GLTextRenderer::getDepthTextureUnit()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void GLTextRenderer::setColourTextureUnit(unsigned int unit)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void GLTextRenderer::setDepthTextureUnit(unsigned int unit)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void GLTextRenderer::addPPFloat(const std::string& name, float* data)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void GLTextRenderer::addPPInt(const std::string& name, int* data)
	{
		throw std::logic_error("The method or operation is not implemented.");
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

			Character ch(
				m_Tex,
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

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(m_posX, m_posY, 0.0f));
		model = glm::scale(model, glm::vec3(glm::vec2(m_Scale), 1.0f));

		std::string::const_iterator c;
		for (c = m_text.begin(); c != m_text.end(); c++) {
			Character Char = m_characters[*c];

			float xpos = x + Char.getBearing().x; 
			float ypos = y + Char.getBearing().y; 

			float width = Char.getSize().x;
			float height = Char.getSize().y;

			float vertices[6][4] = {
				{xpos, ypos + height, 0.0, 0.0},
				{xpos, ypos, 0.0, 1.0},
				{xpos + width, ypos, 1.0, 1.0},

				{xpos, ypos + height, 0.0, 0.0},
				{xpos + width, ypos, 1.0, 1.0},
				{xpos + width, ypos + height, 1.0, 0.0},
			};

			float quadVertices[] = {
				// positions        // texture Coords
				-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
				-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
				 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
				 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			};

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(xpos, ypos, 0.0f));
			model = glm::scale(model, glm::vec3(glm::vec2(m_Scale), 1.0f));

			mat->setDataElement("u_model", (void*)&model[0][0]);

			VAO->getVertexBuffer()[0]->Edit(quadVertices, sizeof(quadVertices), 0);
			

			unsigned int indicies[] = {0,1,2,3,2,1};

			std::shared_ptr<IndexBuffer> ibo;
			ibo.reset(IndexBuffer::Create(indicies, sizeof(indicies)));

			VAO->addIndexBuffer(ibo);

			VAO->Bind();

			unsigned int slot = 0;

			Char.getTexture()->bind(slot);

			mat->setDataElement("u_texData", (void*)&slot);

			NG_INFO("Rendering string '{0}' at position {1}, {2} at size {3}", m_text, xpos, ypos, m_Scale);

			//glDrawArrays(GL_TRIANGLES, 0, 6);

			glDrawElements(GL_TRIANGLES, VAO->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);

			x += (Char.getAdvance() >> 6) * m_Scale;
		}

	}
}