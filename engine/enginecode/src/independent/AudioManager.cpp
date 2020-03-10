#pragma once

/** \file AudioManger.cpp
*/

#include "engine_pch.h"
#include "Audio/AudioManager.h"
#include "systems/log.h"

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
		errorCheck(FMOD::System_Create(&m_lowLevelSystem));
		errorCheck(m_lowLevelSystem->getVersion(&version));
		
		if (version < FMOD_VERSION)
		{
			NG_FATAL("FMOD lib version{0} doesn't match header version {1}", version, FMOD_VERSION);
		}

		errorCheck(m_lowLevelSystem->init(m_maxChannels, FMOD_INIT_NORMAL, NULL));
		errorCheck(m_lowLevelSystem->set3DSettings(1.f, 1.f, 1.f));
		errorCheck(m_lowLevelSystem->setGeometrySettings(50.f));
	
	}

	void AudioManager::stop(SystemSignal close, ...)
	{
	}

	void AudioManager::update()
	{
		//Delete channel from the map once they have been played
		std::vector<std::map<int, FMOD::Channel*>::iterator> l_stoppedChannels;
		for (auto it = m_channels.begin(); it !=m_channels.end(); ++it)
		{
			bool isPlaying = false;
			it->second->isPlaying(&isPlaying);
			if (!isPlaying)
			{
				l_stoppedChannels.push_back(it);
			}

		}
		for (auto& it : l_stoppedChannels)
		{
			m_channels.erase(it);

		}

		// update the low level ststem
		errorCheck(m_lowLevelSystem->update());
		// update the studio system
		errorCheck(m_studioSystem->update());
	}

	void AudioManager::loadBank(const std::string & strBankName, FMOD_STUDIO_LOAD_BANK_FLAGS flags)
	{
	}

	void AudioManager::loadEvent(const std::string & strEventName)
	{
	}

	void AudioManager::loadSound(const std::string & strSoundName, bool b3d, bool bLooping, bool bStream)
	{
		auto it = m_sounds.find(strSoundName);
		if (it != m_sounds.end())
			return;
		FMOD_MODE eMode = FMOD_DEFAULT;
		eMode |= b3d ? FMOD_3D  : FMOD_2D ;
		eMode |= bLooping ? FMOD_LOOP_NORMAL :FMOD_LOOP_OFF ;
		eMode |= bStream ? FMOD_CREATESTREAM :FMOD_CREATECOMPRESSEDSAMPLE ;
		/*switch (rollOff)
		{
			
		}*/
		FMOD::Sound* sound = nullptr;
		errorCheck(m_lowLevelSystem->createSound(strSoundName.c_str(), eMode, 0, &sound));

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

