#include "engine_pch.h"
#include "Renderer\Renderer.h"
#include "Renderer\RenderAPI.h"

#include "GLFW\GLRenderer.h"
#include "GLFW\GLText.h"
#include "GLFW\GLPostProcessRenderer.h"

namespace Engine {
	RenderCommand * RenderCommand::ClearDepthColourBufferCommand()
	{
		switch (RenderAPI::getApi()) {
		case RenderAPI::API::None: return nullptr;
		case RenderAPI::API::OpenGL: return new GLClearDepthColourBufferCommand();
		}
		return nullptr;
	}
	RenderCommand * RenderCommand::setClearColourCommand(float r, float g, float b, float a)
	{
		switch (RenderAPI::getApi()) {
		case RenderAPI::API::None: return nullptr;
		case RenderAPI::API::OpenGL: return new GLSetClearColourCommand(r, g, b, a);
		}
		return nullptr;
	}
	RenderCommand * RenderCommand::setDepthTestLessCommand(bool enabled)
	{
		switch (RenderAPI::getApi()) {
		case RenderAPI::API::None: return nullptr;
		case RenderAPI::API::OpenGL: return new GLsetDepthTestLessCommand(enabled);
		}
		return nullptr;
	}
	RenderCommand * RenderCommand::setBackfaceCullingCommand(bool enabled)
	{
		switch (RenderAPI::getApi()) {
		case RenderAPI::API::None: return nullptr;
		case RenderAPI::API::OpenGL: return new GLsetBackfaceCullingCommand(enabled);
		}
		return nullptr;
	}
	RenderCommand * RenderCommand::setOneMinusAlphaBlending(bool enabled)
	{
		switch (RenderAPI::getApi()) {
		case RenderAPI::API::None: return nullptr;
		case RenderAPI::API::OpenGL: return new GLsetOneMinusAlphaBlendingCommand(enabled);
		}
		return nullptr;
	}
	Renderer * Renderer::createBasic3D()
	{
		switch (RenderAPI::getApi()) {
		case RenderAPI::API::None: return nullptr;
		case RenderAPI::API::OpenGL: return new GLSuperSimpleRenderer();
		}
		return nullptr;
	}

	Engine::Renderer* Renderer::createPostProcess3D()
	{
		switch (RenderAPI::getApi()) {
		case RenderAPI::API::None: return nullptr;
		case RenderAPI::API::OpenGL: return new GLPostProcessRenderer();
		}
		return nullptr;
	}

	Renderer * Renderer::createBasicText2D()
	{
		switch (RenderAPI::getApi()) {
		case RenderAPI::API::None: return nullptr;
		case RenderAPI::API::OpenGL: return new GLTextRenderer();
		}
		return nullptr;
	}
}