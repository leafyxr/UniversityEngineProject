/** \file resourceManager.cpp
*/
#include "engine_pch.h"

#include "systems/ResourceManager.h"

namespace Engine
{
	AssetManager<Shader> ResourceManager::m_shaders;

	template <class G>
	bool AssetManager<G>::contains(const std::string& key)
	{
		auto it = m_container.begin();
		while (it != m_container.end())
		{
			if (it->first == key)
				return true;
			it++;
		}
		return false;
	}

	template <class G>
	std::shared_ptr<G> AssetManager<G>::get(const std::string& key)
	{
		if (contains(key))
			return std::shared_ptr<G>(m_container.at(key));
		else
			return nullptr;
	}

	template <class G>
	void AssetManager<G>::add(const std::string& key, std::shared_ptr<G>& element)
	{
		if (contains(key))
		{
			NG_WARN("'{0}' is already in the container ", key);
		}
		else
		{
			m_container.insert(std::pair<std::string, std::shared_ptr<G>>(key, element));
		}
	}

	std::shared_ptr<Shader> ResourceManager::addShader(const std::string & name)
	{
		m_shaders.add(name, std::shared_ptr<Shader>(Shader::create(name)));
		return std::shared_ptr<Shader>(m_shaders.get(name));
	}
}