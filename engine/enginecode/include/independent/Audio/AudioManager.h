#pragma once

/** \file AudioManger.h
*/

#include "systems/system.h"
#include "..\..\FMOD\core\inc\fmod.hpp"
#include "..\..\FMOD\studio\inc\fmod_studio.hpp"
#include "glm/glm.hpp"
#include <map>

namespace Engine 
{
	class AudioManager : public System
	{
	private:
		FMOD::Studio::System* m_studioSystem;
		FMOD::System* m_lowLevelSystem;

		static const int m_maxChannels = 32;
		int m_nextChannelId = 0;

		std::map<std::string, FMOD::Sound*> m_sounds ;
		std::map<int, FMOD::Channel*> m_channels ;
		std::map<std::string, FMOD::Geometry*> m_geometry ;
		std::map<std::string, FMOD::Studio::EventInstance> m_events ;
		std::map<std::string, FMOD::Studio::Bank*> m_banks ;
		int errorCheck(FMOD_RESULT result) const;
		FMOD_VECTOR GLMVecToFmod(const glm::vec3& vec);

	public:
		void start(SystemSignal init = SystemSignal::None,...); //!< Start system
		void stop(SystemSignal close = SystemSignal::None,...); //!< stop system
		void update();
		void  loadBank(const std::string& strBankName, FMOD_STUDIO_LOAD_BANK_FLAGS flags);
		void loadEvent(const std::string& strEventName);
		void loadSound(const std::string& strSoundName, bool b3d = true, bool bLooping = false,
			bool bStream= false) ;

		void unLoadSound(const std::string &strSoundname);
		void set3dListenerAndOrientation(const glm::vec3& position, const glm::vec3& forward, const glm::vec3& up);
		void addGeometry(const std::string& label, const AudioGeometryDefinition&  def);
		void moveGeometry(const std::string& label, const glm::vec3& position);
		int  playSound(const std::string &strSoundName, const glm::vec3& vPos = glm::vec3(0, 0, 0));
		void playEvent(const std::string &strEventName);
		void toggleChannelPause(int nChannelId);
		void stopEvent(const std::string &strEventName, bool bImmediate = false);
		void getEventParameter(const std::string &strEventName, const std::string &strEventParameter, float* value);
		void setEventParameter(const std::string &strEventName, const std::string &strParameterName, float value);
		void  setEventPosition(const std::string &strEventName, const glm::vec3& position);
		void  togglePauseAllChannels();
		void  setChannels3dPosition(int nChannelId, const glm::vec3&vPosition);
		bool  isPlaying(int nChannelId) const;
		bool  isEventPlaying(const std::string &strEventName) const;

	};


}
