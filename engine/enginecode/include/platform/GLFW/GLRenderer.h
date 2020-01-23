/** \file GLRenderer.h
*/
#pragma once
#include "Renderer\Renderer.h"

namespace Engine {

	/**
	\class GLClearDepthColourBufferCommand
	GLFW implentation of a Clear Depth Colour Buffer Command
	*/
	class GLClearDepthColourBufferCommand : public RenderCommand {
	private:
	public:
		//! Constructor
		GLClearDepthColourBufferCommand() {};
		//! action
		void action() override;
	};
	/**
	\class GLSetClearColourCommand
	GLFW implentation of a Set Clear Colour Command
	*/
	class GLSetClearColourCommand : public RenderCommand {
	private:
		float m_r, m_g, m_b, m_a;//!< Colour Values
	public:
		//! Constructor
		/*!
		\param r, decimal value for red
		\param g, decimal value for green
		\param b, decimal value for blue
		\param a, decimal value for alpha
		*/
		GLSetClearColourCommand(float r, float g, float b, float a) : m_r(r), m_g(g), m_b(b), m_a(a) {};
		//! action
		void action() override;
	};
	/**
	\class GLsetDepthTestLessCommand
	GLFW implentation of a Set Depth Test Less Command
	*/
	class GLsetDepthTestLessCommand : public RenderCommand {
	private:
		bool m_enabled;//!< Is Enabled?
	public:
		//! Constructor
		/*!
		\param enabled, is enabled?
		*/
		GLsetDepthTestLessCommand(bool enabled) : m_enabled(enabled) {};
		//! action
		void action() override;
	};
	/**
	\class GLsetBackfaceCullingCommand
	GLFW implentation of a Set Backface Culling Command
	*/
	class GLsetBackfaceCullingCommand : public RenderCommand {
	private:
		bool m_enabled;//!< Is Enabled?
	public:
		//! Constructor
		/*!
		\param enabled, is enabled?
		*/
		GLsetBackfaceCullingCommand(bool enabled) : m_enabled(enabled) {};
		//! action
		void action() override;
	};
	/**
	\class GLSuperSimpleRenderer
	GLFW implentation of a Super Simple 3D Renderer
	*/
	class GLSuperSimpleRenderer : public Renderer {
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