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
		// need help with 
		m_lowLevelSystem->release();
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
		auto it = m_banks.find(strBankName);
		if (it != m_banks.end())
			return;
		FMOD::Studio::Bank* bank;
		errorCheck(m_studioSystem->loadBankFile(strBankName.c_str(), flags, &bank));
		if (bank) {
			m_banks[strBankName] = bank;
		}
	}
	void AudioManager::loadEvent(const std::string & strEventName)
	{
		auto it = m_events.find(strEventName);
		if (it != m_events.end())
			return;
		FMOD::Studio::EventDescription* eventDescription = NULL;
		errorCheck(m_studioSystem->getEvent(strEventName.c_str(), &eventDescription));
		if (eventDescription) {
			FMOD::Studio::EventInstance* eventInstance = NULL;
			errorCheck(eventDescription->createInstance(&eventInstance));
			if (eventInstance) {
				m_events[strEventName] = eventInstance;
			}
		}
	}

	void AudioManager::loadSound(const std::string & strSoundName, bool b3d, bool bLooping, bool bStream, float minDist, float maxDist)
	{
		auto it = m_sounds.find(strSoundName);
		if (it != m_sounds.end())
			return;
		FMOD_MODE eMode = FMOD_DEFAULT;
		eMode |= b3d ? FMOD_3D  : FMOD_2D ;
		eMode |= bLooping ? FMOD_LOOP_NORMAL :FMOD_LOOP_OFF ;
		eMode |= bStream ? FMOD_CREATESTREAM :FMOD_CREATECOMPRESSEDSAMPLE ;
		

		FMOD::Sound* sound = nullptr;
		errorCheck(m_lowLevelSystem->createSound(strSoundName.c_str(), eMode, 0, &sound));

		if (b3d)
		{
			sound->set3DMinMaxDistance(minDist, maxDist);
		}
		if (sound != nullptr)
		{
			m_sounds[strSoundName] = sound;
		}
	}

	void AudioManager::unLoadSound(const std::string & strSoundName)
	{
		auto it = m_sounds.find(strSoundName);
		if (it != m_sounds.end())
			return;
		it->second->release();
		m_sounds.erase(it);

	}

	void AudioManager::set3dListenerAndOrientation(const glm::vec3 & position, const glm::vec3 & forward, const glm::vec3 & up)
	{
		FMOD_VECTOR lastPos, lastVel, lastForward, lastUP;

		errorCheck(m_lowLevelSystem->get3DListenerAttributes(0, &lastPos, &lastVel, &lastForward, &lastUP));

		auto listernerPos = GLMVecToFmod(position);
		auto listernerForward = GLMVecToFmod(forward);
		auto listernerUp = GLMVecToFmod(up);

		FMOD_VECTOR vel;
		vel.x = (listernerPos.x - lastPos.x ) * (1.0f / 60.f);
		vel.y = (listernerPos.y - lastPos.y ) * (1.0f / 60.f);
		vel.z = (listernerPos.z - lastPos.z ) * (1.0f / 60.f);


		errorCheck(m_lowLevelSystem->set3DListenerAttributes(0, &listernerPos, &vel, &listernerForward, &listernerUp));
	}

	void AudioManager::addGeometry(const std::string & label, const AudioGeometryDefinition & def)
	{
		FMOD::Geometry *geometry;

		int numPolys = def.indices.size() / 3; //assume triangles are being used

		errorCheck(m_lowLevelSystem->createGeometry(numPolys, def.verticies.size(), &geometry));

		m_geometry[label] = geometry;
		FMOD_VECTOR triangle[3];
		FMOD_VECTOR vert = { 0,0,0 };
		int polygonIndex;

		for (int i = 0, j = 0; i <def.verticies.size(); i++)
		{
			vert.x = def.verticies[i]; i++;
			vert.y = def.verticies[i]; i++;
			vert.z = def.verticies[i]; 
			triangle[j] = vert;
			j++;

			if (j == 3)
			{
				geometry->addPolygon(def.directOcculstion, def.reverbOcculsion, true, 3, triangle, &polygonIndex);
				j = 0;
			}

		}
		geometry->setScale(&GLMVecToFmod(def.scale));
		geometry->setPosition(&GLMVecToFmod(def.position));

	}

	void AudioManager::moveGeometry(const std::string & label, const glm::vec3 & position)
	{
		m_geometry[label]->setPosition(&GLMVecToFmod(position));

	}

	int AudioManager::playSound(const std::string & strSoundName, const glm::vec3 & vPos)
	{
		int channelID = m_nextChannelId++;
		auto it = m_sounds.find(strSoundName);
		if (it == m_sounds.end())
		{
			return channelID;
		}
		FMOD::Channel* channel = nullptr;
errorCheck(m_lowLevelSystem->playSound(it->second, 0, true, &channel));
if (channel)
{
	FMOD_MODE currMode;
	it->second->getMode(&currMode);
	if (currMode & FMOD_3D) {
		FMOD_VECTOR FVposition = GLMVecToFmod(vPos);
		FMOD_VECTOR vel = { 0.0f, 0.0f, 0.0f };
		errorCheck(channel->set3DAttributes(&FVposition, &vel));
	}
	errorCheck(channel->setPaused(false));
	m_channels[channelID] = channel;
}
return channelID;
	}

	void AudioManager::playEvent(const std::string & strEventName)
	{
		auto it = m_events.find(strEventName);
		if (it != m_events.end()) {
			loadEvent(strEventName);
			it = m_events.find(strEventName);
			if (it == m_events.end())
				return;
		}

	}

	void AudioManager::toggleChannelPause(int nChannelId)
	{
		bool currentlyPause = false;
		m_channels[nChannelId]->getPaused(&currentlyPause);
		m_channels[nChannelId]->setPaused(!currentlyPause);
	}

	void AudioManager::stopEvent(const std::string & strEventName, bool bImmediate)
	{
		auto it = m_events.find(strEventName);
		if (it != m_events.end())
			return;
		FMOD_STUDIO_STOP_MODE eMode;
		eMode = bImmediate ? FMOD_STUDIO_STOP_IMMEDIATE : FMOD_STUDIO_STOP_ALLOWFADEOUT;
		errorCheck(it->second->stop(eMode));
	}

	void AudioManager::getEventParameter(const std::string & strEventName, const std::string & strEventParameter, float*  value)
	{
		auto it = m_events.find(strEventName);
		if (it == m_events.end())
			return;

		errorCheck(it->second->getParameterByName(strEventParameter.c_str(), value));
	}

	void AudioManager::setEventParameter(const std::string & strEventName, const std::string & strParameterName, float value)
	{
		auto it = m_events.find(strEventName);
		if (it == m_events.end())
			return;

		errorCheck(it->second->setParameterByName(strParameterName.c_str(), value));
	}

	void AudioManager::setEventPosition(const std::string & strEventName, const glm::vec3 & position)
	{
		auto it = m_events.find(strEventName);
		if (it == m_events.end())
			return;

		FMOD_VECTOR Position = GLMVecToFmod(position);
		//errorCheck(it->second.set3DAttributes(&Position, NULL));

	}

	void AudioManager::togglePauseAllChannels()
	{
	/*	bool currentChannelsPause = false;
		if (currentChannelsPause == true)
		{
			m_channels[0]->setPaused;
		}
		else
		{
			m_channels[0]->getPaused;
		}*/
		bool Paused;
		for (auto it = m_channels.begin(); it != m_channels.end(); ++it)
		{
			it->second->getPaused(&Paused);
			Paused = !Paused;
			it->second->setPaused(Paused);
			
		}


		
			

	}

	void AudioManager::setChannels3dPosition(int nChannelId, const glm::vec3 & vPosition)
	{
		auto it = m_channels.find(nChannelId);
		if (it == m_channels.end())
			return;

		FMOD_VECTOR position = GLMVecToFmod(vPosition);
		errorCheck(it->second->set3DAttributes(&position, NULL));
	}

	bool AudioManager::isPlaying(int nChannelId) const
	{
		auto it = m_channels.find(nChannelId);
		if (it == m_channels.end())
			return false;

		bool Playing;
		it->second->isPlaying(&Playing); 
		return Playing;

	}

	bool AudioManager::isEventPlaying(const std::string & strEventName) const
	{
		auto it = m_events.find(strEventName);
		if(it == m_events.end())
		return false;

		FMOD_STUDIO_PLAYBACK_STATE* state = NULL;
		if (it->second->getPlaybackState(state) == FMOD_STUDIO_PLAYBACK_PLAYING) {
			return true;
		}
		return false;

	}


}

