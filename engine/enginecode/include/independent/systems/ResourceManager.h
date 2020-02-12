/** \file application.h
*/
#pragma once

#include "system.h"
#include "log.h"

#include "Renderer/Shader.h"

#include <string>
#include <map>

namespace Engine
{
	template <class G>
	class AssetManager
	{
	public:
		bool contains(const std::string& key); //!< Is this item in the container already?
		void add(const std::string& key, std::shared_ptr<G>& element); //!< Add element to the container
		std::shared_ptr<G> get(const std::string& key); //!< Get a point to an asset. Return nullptr if not found
	private:
		std::map<std::string, std::shared_ptr<G>> m_container; //Data structure to hold assets
	};

	class ResourceManager : public System
	{
	private:
		static AssetManager<Shader> m_shaders;

	public:
		void start(SystemSignal init, ...) {}; //!< Start the system
		void stop(SystemSignal close, ...) {}; //!< Stop the system - change this to free all resources


		//static add functions
		static std::shared_ptr<Shader> addShader(const std::string& name);
	};
}
