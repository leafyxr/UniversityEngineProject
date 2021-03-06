#pragma once
#include <systems/componentSystem.h>


class FlatCube : public Engine::GameObject
{
private:
	glm::mat4 m_model;
	Engine::OscilateComponent::state m_state;
	float m_elapsedTime = 0;
public:
	void sendMessage(const Engine::ComponentMessage& msg) override;
	void onUpdate(float timestep) override;
	void onEvent(Engine::Event& e) override;
	void addComponent(const std::shared_ptr<Engine::Component>& comp) override;
	void removeComponent(std::vector<std::shared_ptr<Engine::Component>>::iterator iter) override;
};
