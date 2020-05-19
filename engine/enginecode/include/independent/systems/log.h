/** \file log.h
*/
#pragma once
#include "spdlog\spdlog.h"
#include "system.h"

namespace Engine {
	/**
	\class Log
	Logger System class
	*/
	class Log : System
	{
	private:
		static bool bActive;//!< is active
		static std::shared_ptr<spdlog::logger> s_Logger;//!< logger
	public:
		//!Start
		 static void start(SystemSignal init = SystemSignal::None);
		 //!Stop
		 static void stop(SystemSignal init = SystemSignal::None);
		 //! is Active
		 /*!
		 \return if active
		 */
		 static bool IsActive() { return bActive; }
		 //! get logger
		 /*!
		 \return logger
		 */
		 static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }
	};
}

//Log Macro's
#define NG_TRACE(...)		::Engine::Log::GetLogger()->trace(__VA_ARGS__)//!< Logger Trace
#define NG_INFO(...)		::Engine::Log::GetLogger()->info(__VA_ARGS__)//!< Logger Info
#define NG_WARN(...)		::Engine::Log::GetLogger()->warn(__VA_ARGS__)//!< Logger Warn
#define NG_ERROR(...)		::Engine::Log::GetLogger()->error(__VA_ARGS__)//!< Logger Error
#define NG_FATAL(...)		::Engine::Log::GetLogger()->critical(__VA_ARGS__)//!< Logger Fatal
#define NG_ASSERT(x, ...) { if(!(x)) { NG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }//!< Logger Assert
