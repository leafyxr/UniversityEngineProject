/** \file entityComponentSystem.h
*/

#pragma once

#include "events/Event.h"
#include <any>

#include <renderer/material.h>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Engine
{
	enum class ComponentMessageType
	{
		None = 0,
		PositionIntegrate, PositionSet, RelativePositionSet,
		VelocityIntegrate, VelocitySetLinear, VelocitySetAngular,
		AccelerationSet,
		KeyPressed, KeyReleased, MouseButton, MouseScroll, MouseMoved,
		UniformSet, TextureSet
	};

	class ComponentMessage
	{
	public:
		ComponentMessage(ComponentMessageType type, std::any data) : m_msgType(type), m_msgData(data) {}
		ComponentMessageType m_msgType; //!< Message type
		std::any m_msgData; //!< Data associated with the message (could use a void *)
	};

	class GameObject;

	class Component
	{
	protected:
		GameObject* m_owner = nullptr; //!< Owner of the component, using a raw pointer as there is no ownership
		virtual void sendMessage(const ComponentMessage& msg);
	public:
		virtual void onAttach(GameObject* owner) { m_owner = owner; }
		virtual void onDetach() { m_owner = nullptr; }
		virtual void onUpdate(float timestep) {}
		virtual void onEvent(Event& e) {}
		virtual void receiveMessage(const ComponentMessage& msg) = 0;
	};

	class GameObject
	{
	protected:
		std::vector<std::shared_ptr<Component>> m_components;
	public:
		void sendMessage(const ComponentMessage& msg);
		void onUpdate(float timestep);
		void onEvent(Event& e);
		void addComponent(const std::shared_ptr<Component>& comp);
		void removeComponent(std::vector<std::shared_ptr<Component>>::iterator iter);
		template<typename G>
		std::vector<std::shared_ptr<Component>>::iterator getComponent()
		{
			auto result = m_components.end();
			for (auto it = m_components.begin(); it != m_components.end(); ++it)
			{
				if (typeid(decltype(*(it->get()))).hash_code() == typeid(G).hash_code())
					return it;
			}
			return result;
		}

		inline std::vector<std::shared_ptr<Component>>::iterator begin() { return m_components.begin(); }
		inline std::vector<std::shared_ptr<Component>>::iterator end() { return m_components.end(); }
	};

	class MaterialComponent : public Component
	{
	private:
		std::shared_ptr<Material> m_material;
	public:
		MaterialComponent(const std::shared_ptr<Material>& material) : m_material(material) {}
		inline std::shared_ptr<Material> getMaterial() { return m_material; }
		void receiveMessage(const ComponentMessage& msg) override
		{
			switch (msg.m_msgType)
			{
			case ComponentMessageType::UniformSet:
				std::pair<std::string, void*> data = std::any_cast<std::pair<std::string, void*>>(msg.m_msgData);
				m_material->setDataElement(data.first, data.second);
				return;
			}
		}
	};


	//POSITION COMPONENT
	class PositionComponent : public Component
	{
	private:
		glm::mat4 m_model;
		glm::mat4 m_translation;
		glm::mat4 m_rotation;
		glm::mat4 m_scale;
		glm::vec3 m_transVec;
		glm::vec3 m_rotVec;
		glm::vec3 m_scaleVec;
		inline void calculateModel()
		{
			m_translation = glm::translate(glm::mat4(1.0f), m_transVec);
			m_rotation = glm::toMat4(glm::quat(m_rotVec));
			m_scale = glm::scale(m_scaleVec);
			m_model = m_translation * m_rotation * m_scale;
		}
	public:
		PositionComponent(glm::vec3 trans, glm::vec3 rot, glm::vec3 scale) :
			m_transVec(trans), m_rotVec(rot), m_scaleVec(scale), m_model(glm::mat4(1.0f))
		{
			m_rotVec.x = glm::radians(m_rotVec.x);
			m_rotVec.y = glm::radians(m_rotVec.y);
			m_rotVec.z = glm::radians(m_rotVec.z);
			calculateModel();
		}
		inline std::shared_ptr<glm::mat4> getTransform() { return std::make_shared<glm::mat4>(m_model); }
		void receiveMessage(const ComponentMessage& msg) override
		{
			switch (msg.m_msgType)
			{
			case ComponentMessageType::PositionSet:
			{
				glm::vec3 pos = std::any_cast<glm::vec3>(msg.m_msgData);
				m_transVec = pos;
				calculateModel();
				return;
			}
			case ComponentMessageType::PositionIntegrate:
			{
				std::pair<glm::vec3, glm::vec3> vel = std::any_cast<std::pair<glm::vec3, glm::vec3>>(msg.m_msgData);

				m_transVec += vel.first;
				m_rotVec.x += glm::radians(vel.second.x);
				m_rotVec.y += glm::radians(vel.second.y);
				m_rotVec.z += glm::radians(vel.second.z);
				calculateModel();
				return;
			}
			}
		}
		void onUpdate(float timestep) override
		{
			std::pair<std::string, void*> data("u_MVP", (void*)&m_model[0][0]);
			ComponentMessage msg(ComponentMessageType::UniformSet, data);
			sendMessage(msg);
		}
		void onAttach(GameObject* owner)override
		{
			m_owner = owner;
			std::pair<std::string, void*> data("u_MVP", (void*)&m_model[0][0]);
			ComponentMessage msg(ComponentMessageType::UniformSet, data);
			sendMessage(msg);
		}
	};
	//VELOCITY COMPONENT
	class VelocityComponent : public Component
	{
	private:
		glm::vec3 m_linear;
		glm::vec3 m_angular;
	public:
		VelocityComponent(glm::vec3 linear, glm::vec3 angular) : m_linear(linear), m_angular(angular) {}
		void receiveMessage(const ComponentMessage& msg) override
		{
			switch (msg.m_msgType)
			{
			case ComponentMessageType::VelocitySetLinear:
			{
				glm::vec3 linear = std::any_cast<glm::vec3>(msg.m_msgData);
				m_linear = linear;
				return;
			}
			case ComponentMessageType::PositionIntegrate:
			{
				auto pair = std::any_cast<std::pair<glm::vec3, glm::vec3>>(msg.m_msgData);
				m_angular = pair.second;
				m_linear = pair.first;
				return;
			}
			}
		}
		void onUpdate(float timestep) override
		{
			std::pair<glm::vec3, glm::vec3> data(m_linear * timestep, m_angular* timestep);
			sendMessage(ComponentMessage(ComponentMessageType::PositionIntegrate, std::any(data)));
		}
	};
}
