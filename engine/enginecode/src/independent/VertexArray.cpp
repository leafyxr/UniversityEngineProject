#include "engine_pch.h"
#include "Renderer\VertexArray.h"
#include "Renderer\RenderAPI.h"
#include "GLFW\VertexArrayGL.h"

namespace Engine {

	VertexArray * VertexArray::Create()
	{
		switch (RenderAPI::getApi()) {
		case RenderAPI::API::None: return nullptr;
		case RenderAPI::API::OpenGL: return new VertexArrayGL();
		}
		return nullptr;
	}

}