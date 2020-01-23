#include "engine_pch.h"
#include "core\Timer.h"
#include "systems\Log.h"

namespace Engine {
	bool Timer::bActive = false;
	std::chrono::high_resolution_clock::time_point Timer::m_StartTime;
	std::chrono::high_resolution_clock::time_point Timer::m_EndTime;
	std::chrono::duration<float> Timer::m_FrameDuration;

	void Timer::start(SystemSignal init)
	{
		if (!bActive) {
			m_StartTime = std::chrono::high_resolution_clock::now();
			bActive = true;
		}
		else {
			NG_ERROR("Timer is already active");
		}
	}
	void Timer::stop(SystemSignal init)
	{
		if (bActive) {
			bActive = false;
		}
		else {
			NG_ERROR("Timer is not active");
		}
	}
	void Timer::update()
	{
		if(bActive) {
			m_EndTime = std::chrono::high_resolution_clock::now();
			m_FrameDuration = m_EndTime - m_StartTime;

			m_StartTime = std::chrono::high_resolution_clock::now();
		}
	}
}