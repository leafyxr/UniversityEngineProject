#pragma once
#include "Renderer\Renderer.h" 
#include "Renderer\Text.h"

namespace Engine {

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
	};

}