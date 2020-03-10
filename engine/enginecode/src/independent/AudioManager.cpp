#pragma once

/** \file AudioManger.cpp
*/

#include "engine_pch.h"
#include "Audio/AudioManager.h"

namespace Engine
{
	int Engine::AudioManager::errorCheck(FMOD_RESULT result) const
	{
		return 0;
	}

	FMOD_VECTOR Engine::AudioManager::GLMVecToFmod(const glm::vec3 & vec)
	{
		return FMOD_VECTOR();
	}

	void AudioManager::start(SystemSignal init, ...)
	{
		errorCheck(FMOD::Studio::System::create(&m_studioSystem));
		errorCheck(m_studioSystem->initialize(m_maxChannels, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, NULL));

		unsigned int version;
		errorCheck(());
		errorCheck(());
		
		if (version < FMOD_VERSION)
		{

		}

		errorCheck(());
		errorCheck(());
		errorCheck(());
	
	}

	void AudioManager::stop(SystemSignal close, ...)
	{
	}

	void AudioManager::update()
	{
	}

	void AudioManager::loadBank(const std::string & strBankName, FMOD_STUDIO_LOAD_BANK_FLAGS flags)
	{
	}

	void AudioManager::loadEvent(const std::string & strEventName)
	{
	}

	void AudioManager::loadSound(const std::string & strSoundName, bool b3d, bool bLooping, bool bStream)
	{
	}

	void AudioManager::unLoadSound(const std::string & strSoundname)
	{
	}

	void AudioManager::set3dListenerAndOrientation(const glm::vec3 & position, const glm::vec3 & forward, const glm::vec3 & up)
	{
	}

	void AudioManager::addGeometry(const std::string & label, const AudioGeometryDefinition & def)
	{
	}

	void AudioManager::moveGeometry(const std::string & label, const glm::vec3 & position)
	{
	}

	int AudioManager::playSound(const std::string & strSoundName, const glm::vec3 & vPos)
	{
		return 0;
	}

	void AudioManager::playEvent(const std::string & strEventName)
	{
	}

	void AudioManager::toggleChannelPause(int nChannelId)
	{
	}

	void AudioManager::stopEvent(const std::string & strEventName, bool bImmediate)
	{
	}

	void AudioManager::getEventParameter(const std::string & strEventName, const std::string & strEventParameter, float * value)
	{
	}

	void AudioManager::setEventParameter(const std::string & strEventName, const std::string & strParameterName, float value)
	{
	}

	void AudioManager::setEventPosition(const std::string & strEventName, const glm::vec3 & position)
	{
	}

	void AudioManager::togglePauseAllChannels()
	{
	}

	void AudioManager::setChannels3dPosition(int nChannelId, const glm::vec3 & vPosition)
	{
	}

	bool AudioManager::isPlaying(int nChannelId) const
	{
		return false;
	}

	bool AudioManager::isEventPlaying(const std::string & strEventName) const
	{
		return false;
	}


}

