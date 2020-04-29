#include "engine_pch.h"
#include "Renderer/Text.h"
#include "Renderer/RenderAPI.h"
#include "GLFW/GLText.h"

namespace Engine {

	bool Text::s_Init = false;

	Text * Text::create(const std::string& filepath) {
		switch (RenderAPI::getApi()) {
		case RenderAPI::API::None:			return nullptr;
		case RenderAPI::API::OpenGL:		return  new GLText(filepath);
		}
		return nullptr;
	}
}///4:45