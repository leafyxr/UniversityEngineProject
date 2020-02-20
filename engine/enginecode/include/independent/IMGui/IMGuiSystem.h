#pragma once

#include <imgui.h>
#include <examples/imgui_impl_opengl3.cpp>
#include <examples/imgui_impl_glfw.cpp>
#include "systems/system.h"

//#include <cstdarg>

namespace Engine {
	void start(SystemSignal sig, ...);
	void stop(SystemSignal sig, ...);
}