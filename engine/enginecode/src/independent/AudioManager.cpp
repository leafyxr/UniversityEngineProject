#pragma once

/** \file AudioManger.cpp
*/

#include "engine_pch.h"
#include "Audio/AudioManager.h"

int Engine::AudioManager::errorCheck(FMOD_RESULT result) const
{
	return 0;
}

FMOD_VECTOR Engine::AudioManager::GLMVecToFmod(const glm::vec3 & vec)
{
	return FMOD_VECTOR();
}
