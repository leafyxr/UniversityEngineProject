#pragma once

#include <imgui.h>
#include <examples/imgui_impl_opengl3.h>
#include <examples/imgui_impl_glfw.h>
#include "systems/system.h"

//#include <cstdarg>

namespace Engine {
	class IMGuiSystem: public System
	{
	public:
		~IMGuiSystem() override {};
		void start(SystemSignal init = SystemSignal::None, ...) override; //!< Start the system
		void stop(SystemSignal close = SystemSignal::None, ...) override; //!< Stop the system
	};
}