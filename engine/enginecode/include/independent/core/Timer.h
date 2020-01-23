/** \file Timer.h
*/
#pragma once
#include "systems\system.h"
#include <chrono>

namespace Engine {
	/**
	\class Timer
	Basic Timer system
	*/
	class Timer : System {
	private:
		static std::chrono::high_resolution_clock::time_point m_StartTime;
		static std::chrono::high_resolution_clock::time_point m_EndTime;
		static std::chrono::duration<float> m_FrameDuration;
		static bool bActive;
	public:
		static void start(SystemSignal init = SystemSignal::None);
		static void stop(SystemSignal init = SystemSignal::None);
		static void update();
		static float GetFrameSeconds() { return m_FrameDuration.count(); }
		static float GetFrameMilliseconds() { return m_FrameDuration.count() * 1000.0f; }
	};

}