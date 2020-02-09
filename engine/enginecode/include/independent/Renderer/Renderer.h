/** \file Renderer.h
*/
#pragma once
#include "Material.h"

namespace Engine {

	/**
	\class Render Commands
	Base class for render commands
	*/
	class RenderCommand {
	public:
		//! Action
		virtual void action() = 0;

		//! clear depth colour buffer
		static RenderCommand* ClearDepthColourBufferCommand();
		//! set clear colour
		/*!
		\param r
		\param g
		\param b
		\param a
		*/
		static RenderCommand* setClearColourCommand(float r, float g, float b, float a);
		//! Constructor, from individual files
		/*!
		\param VertFilepath, path to vertex shader
		\param FragFilepath, path to fragment shader
		*/
		static RenderCommand* setDepthTestLessCommand(bool enabled);
		//! Constructor, from individual files
		/*!
		\param VertFilepath, path to vertex shader
		\param FragFilepath, path to fragment shader
		*/
		static RenderCommand* setBackfaceCullingCommand(bool enabled);
	};

	/**
	\class Renderer
	Interface for Renderer
	*/
	class Renderer {
	public:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;//!< View Projection Matrix
		};
		//! process command
		/*!
		\param command, command to be processed
		*/
		virtual void actionCommand(RenderCommand* command) = 0;
		//! begin scene
		/*!
		\param sceneData, 
		*/
		virtual void beginScene(const SceneData& sceneData) = 0;
		//! end scene
		virtual void endScene() = 0;
		//!submit material to GPU
		/*!
		\param material
		*/
		virtual void submit(const std::shared_ptr<Material>& material) = 0;
		//!Flush
		virtual void flush() = 0;

		//!Create 3d renderer
		static Renderer* createBasic3D();
	};

}