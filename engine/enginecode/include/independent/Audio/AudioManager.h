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

		void unLoadSound();
		void set3dListenerAndOrientation();
		void addGeometry();
		void moveGeometry();
		int  playSound();
		void playEvent();
		void toggleChannelPause();
		void stopEvent();
		void getEventParameter();
		void setEventParameter();
		void SetEventPosition();
		void  togglePauseAllChannels();
		void  setChannels3dPosition();
		bool  isPlaying() const;
		bool  isEventPlaying() const;

	};


}
