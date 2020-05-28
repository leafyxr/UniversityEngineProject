#include "engine_pch.h"
#include "flatCube.h"
#include <cmath>

void FlatCube::sendMessage(const Engine::ComponentMessage & msg)
{
	for (auto comp : m_components)
	{
		comp->receiveMessage(msg);
	}
}

void FlatCube::onUpdate(float timestep)
{
	m_elapsedTime += timestep;
	for (auto &comp : m_components)
	{
		comp->onUpdate(timestep);
	}

	std::pair<std::string, void*> viewData("u_vp", (void*)&m_vpMatrix[0][0]);
	Engine::ComponentMessage msgView(Engine::ComponentMessageType::UniformSet, viewData);
	sendMessage(msgView);

	
	float id = getObjectIDfloat();
	std::pair<std::string, void*> DataID("u_objectID", (void*)&id);
	Engine::ComponentMessage msgID(Engine::ComponentMessageType::UniformSet, DataID);
	sendMessage(msgID);

	glm::vec3 rotation = glm::vec3(0.f, 10.f, 0.f) * timestep;
	Engine::ComponentMessage msgRotation(Engine::ComponentMessageType::RotationIntegrate, rotation);
	sendMessage(msgRotation);

	glm::vec3 scale = glm::vec3(std::cosf(m_elapsedTime) * 10, std::cosf(m_elapsedTime) * 10, std::cosf(m_elapsedTime) * 10) * timestep;
	Engine::ComponentMessage msgScale(Engine::ComponentMessageType::ScaleIntegrate, scale);
	sendMessage(msgScale);

	//switch (m_state)
	//{
	//case Engine::OscilateComponent::state::UP:
	//	sendMessage(Engine::ComponentMessage(Engine::ComponentMessageType::VelocitySetLinear, std::any(glm::vec3(0.f, 0.2f, 0.f))));
	//	return;
	//case Engine::OscilateComponent::state::DOWN:
	//	sendMessage(Engine::ComponentMessage(Engine::ComponentMessageType::VelocitySetLinear, std::any(glm::vec3(0.f, -0.2f, 0.f))));
	//	return;
	//case Engine::OscilateComponent::state::STOPPED:
	//	return;
	//}
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
