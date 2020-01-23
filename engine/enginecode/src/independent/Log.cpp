#include "engine_pch.h"
#include "systems\Log.h"
#include "spdlog\sinks\stdout_color_sinks.h"

namespace Engine {

	std::shared_ptr<spdlog::logger> Log::s_Logger;
	bool Log::bActive = false;

	 void Log::start(SystemSignal init)
	{
		spdlog::set_pattern("%^[%T] %n: %v%$ ");
		s_Logger = spdlog::stdout_color_mt("ENGINE");
		s_Logger->set_level(spdlog::level::trace);
		bActive = true;
	}

	 void Log::stop(SystemSignal init)
	{
		s_Logger.reset();
		bActive = false;
	}

}
