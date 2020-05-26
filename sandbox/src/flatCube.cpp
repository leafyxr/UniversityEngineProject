#include "engine_pch.h"
#include "flatCube.h"

void FlatCube::sendMessage(const Engine::ComponentMessage & msg)
{
	for (auto comp : m_components)
	{
		comp->receiveMessage(msg);
	}
}

void FlatCube::onUpdate(float timestep)
{
	for (auto &comp : m_components)
	{
		comp->onUpdate(timestep);
	}

	std::pair<std::string, void*> projData("u_projection", (void*)&m_projection[0][0]);
	Engine::ComponentMessage msgProjection(Engine::ComponentMessageType::UniformSet, projData);
	sendMessage(msgProjection);

	std::pair<std::string, void*> viewData("u_view", (void*)&m_view[0][0]);
	Engine::ComponentMessage msgView(Engine::ComponentMessageType::UniformSet, viewData);
	sendMessage(msgView);
}

void FlatCube::onEvent(Engine::Event & e)
{
	for (auto &comp : m_components)
	{
		comp->onEvent(e);
	}
}

void FlatCube::addComponent(const std::shared_ptr<Engine::Component>& comp)
{
	comp->onAttach(this);
	m_components.push_back(comp);
}

void FlatCube::removeComponent(std::vector<std::shared_ptr<Engine::Component>>::iterator iter)
{
	m_components.erase(iter);
}
