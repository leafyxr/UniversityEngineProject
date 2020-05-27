/** \file entityComponentSystem.cpp
*/
#include "engine_pch.h"
#include "systems/componentSystem.h"
#include "systems/log.h"

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

	void OscilateComponent::onAttach(GameObject * owner)
	{
		m_owner = owner;

		//if (m_state == DOWN)
		//{
		//	sendMessage(ComponentMessage(ComponentMessageType::VelocitySetLinear, std::any(glm::vec3(0.f, -0.2f, 0.f))));
		//}
		//else if (m_state == UP)
		//{
		//	sendMessage(ComponentMessage(ComponentMessageType::VelocitySetLinear, std::any(glm::vec3(0.f, 0.2f, 0.f))));
		//}

		//sendMessage(ComponentMessage(ComponentMessageType::TextureSet, std::any(m_state)));
	}

	void OscilateComponent::onDetach()
	{

	}

	void OscilateComponent::onUpdate(float timestep)
	{
		m_timeAccumulated += timestep;
		//NG_INFO("{0}", m_timeAccumulated);

		if (m_state == DOWN)
		{
			sendMessage(ComponentMessage(ComponentMessageType::VelocitySetLinear, std::any(glm::vec3(0.f, -0.2f, 0.f))));
		}
		else if (m_state == UP)
		{
			sendMessage(ComponentMessage(ComponentMessageType::VelocitySetLinear, std::any(glm::vec3(0.f, 0.2f, 0.f))));
		}

		if (m_timeAccumulated >= 20.f && m_state == UP)
		{
			m_timeAccumulated = 0.f;
			m_state = DOWN;

		}
		else if (m_timeAccumulated >= 20.f && m_state == DOWN)
		{
			m_timeAccumulated = 0.f;
			m_state = UP;
		}
	}

	void OscilateComponent::onEvent(Event & e)
	{

	}

	void OscilateComponent::receiveMessage(const ComponentMessage & msg)
	{

	}


}