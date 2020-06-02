/** \file GLText.h
*/

#pragma once
#include "Renderer\Renderer.h" 
#include "Renderer\Text.h"
#include "Renderer/Texture.h"
#include <ft2build.h>
#include <map>
#include FT_FREETYPE_H

namespace Engine {

	/**
	\class GLText
	GLFW implementation of a Text Class
	*/
	class GLText : public Text {
	private:
		std::string m_filePath, m_text;
		float m_posX, m_posY, m_Scale;
		glm::vec3 m_Colour;

		std::shared_ptr<Texture> m_Tex;
		std::map<char, Character> m_characters;

	public:
		GLText(const std::string& path);
		virtual void setText(std::string& text) override { m_text = text; }
		virtual void setPosition(glm::vec2 pos) override { m_posX = pos.x; m_posY = pos.y; }
		virtual void setPosX(float x) override { m_posX = x; }
		virtual void setPosY(float y) override { m_posY = y; }
		virtual void setScale(float scale) override { m_Scale = scale; }
		virtual void setColour(glm::vec3 colour) override { m_Colour = colour; }

		virtual inline std::string getText() override { return m_text; }
		virtual inline glm::vec2 getPosition() override { return glm::vec2(m_posX, m_posY); }
		virtual inline float getPosX() override { return m_posX; }
		virtual inline float getPosY() override { return m_posY; }
		virtual inline float getScale() override { return m_Scale; }
		virtual inline glm::vec3 getColour() override { return m_Colour; }

		virtual void render(std::shared_ptr<Material> mat) override;
	};

	/**
	\class GLClearDepthColourBufferCommand
	GLFW implentation of a Clear Depth Colour Buffer Command
	*/
	class GLTextRenderer : public Renderer {
	private:

	public:
		//! submit a valid render command
		/*!
		\param command, render command to use
		*/
		void actionCommand(RenderCommand* command) override;
		//! Begin Scene
		/*!
		\param sceneData, View Projection Matrix / Camera
		*/
		void beginScene(const SceneData& sceneData) override {}
		//! End Scene
		/*!
		\param enabled, is enabled?
		*/
		void endScene() override {}
		//! Submit
		/*!
		\param material, material to render?
		*/
		void submit(const std::shared_ptr<Material>& material) override;
		//! Flush, currently Unused
		void flush() override {}

		void setPPShader(std::shared_ptr<Shader> shader) override;


		void addPPUniform(const std::string& name, void* data) override;


		void deletePPUniform(const std::string& name) override;


		const int& getColourTextureUnit() override;


		const int& getDepthTextureUnit() override;


		void setColourTextureUnit(unsigned int unit) override;


		void setDepthTextureUnit(unsigned int unit) override;


		void addPPFloat(const std::string& name, float* data) override;


		void addPPInt(const std::string& name, int* data) override;


		float getObjectIDatPixel(int x, int y) override;

	};

}