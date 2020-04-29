/** \file entityComponentSystem.cpp
*/
#include "engine_pch.h"
#include "systems/componentSystem.h"

namespace Engine
{
	void Component::sendMessage(const ComponentMessage& msg)
	{
		m_owner->sendMessage(msg);
	}

	void GameObject::sendMessage(const ComponentMessage & msg)
	{
		for (auto comp : m_components)
		{
			comp->receiveMessage(msg);
		}
	}

	void GameObject::onUpdate(float timestep)
	{
		for (auto &comp : m_components)
		{
			comp->onUpdate(timestep);
		}
	}

	void GameObject::onEvent(Event & e)
	{
		for (auto &comp : m_components)
		{
			comp->onEvent(e);
		}
	}

	void GameObject::addComponent(const std::shared_ptr<Component>& comp)
	{
		comp->onAttach(this);
		m_components.push_back(comp);
	}

	void GameObject::removeComponent(std::vector<std::shared_ptr<Component>>::iterator iter)
	{
		m_components.erase(iter);
	}
}