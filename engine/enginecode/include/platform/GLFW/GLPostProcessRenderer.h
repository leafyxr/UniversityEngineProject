#pragma once
#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"

namespace Engine 
{
	class GLPostProcessRenderer : public Renderer 
	{
	private:
		bool m_Active = false;
		unsigned int m_framebufferID;
		unsigned int m_colourTexture;
		unsigned int m_depthTexture;
		unsigned int m_colourTextureUnit = 0;
		unsigned int m_depthTextureUnit = 1;
		std::shared_ptr<VertexArray> m_screenQuadVAO;
		std::shared_ptr<Shader> m_ppShader;
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
		void beginScene(const SceneData& sceneData) override;
		//! End Scene
		/*!
		\param enabled, is enabled?
		*/
		void endScene() override;
		//! Submit
		/*!
		\param material, material to render?
		*/
		void submit(const std::shared_ptr<Material>& material) override;
		//! Flush, currently Unused
		void flush() override;

		void setPPShader(std::shared_ptr<Shader> shader) override { m_ppShader = shader; };

		void addPPUniform(const std::string& name, void* data) override;


		void deletePPUniform(const std::string& name) override;


		const int& getColourTextureUnit() override { return m_colourTextureUnit; }


		const int& getDepthTextureUnit() override { return m_depthTextureUnit; }


		void setColourTextureUnit(unsigned int unit) override { m_colourTextureUnit = unit; }


		void setDepthTextureUnit(unsigned int unit) override { m_depthTextureUnit = unit; }

		void setFBOdepth();

		void setFBOcolour();

		void renderQuad();

		void addPPFloat(const std::string& name, float* data) override;


		void addPPInt(const std::string& name, int* data) override;

	};
}