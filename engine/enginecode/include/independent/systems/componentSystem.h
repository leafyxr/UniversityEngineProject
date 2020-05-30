/** \file entityComponentSystem.h
*/

#pragma once

#include "events/Event.h"
#include <any>
#include "Renderer/Camera.h"

#include <renderer/material.h>
#include <Renderer/Texture.h>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Engine
{
	enum class ComponentMessageType
	{
		None = 0,
		PositionIntegrate, PositionSet, RelativePositionSet,
		VelocityIntegrate, VelocitySetLinear, VelocitySetAngular,
		RotationIntegrate, RotationSet, ScaleIntegrate, ScaleSet,
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
		glm::mat4 m_vpMatrix;
		glm::vec3 m_lightPos;
		glm::vec3 m_viewPos;
		glm::vec3 m_lightCol;
		static int m_numGO;
		int m_objectID;
		bool m_selected = false;
	public:
		virtual void sendMessage(const ComponentMessage& msg);
		virtual void onAttach();
		virtual void onUpdate(float timestep);
		virtual void onEvent(Event& e);
		virtual void addComponent(const std::shared_ptr<Component>& comp);
		virtual void removeComponent(std::vector<std::shared_ptr<Component>>::iterator iter);
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
		void setViewProjection(glm::mat4 vp) { m_vpMatrix = vp; }
		void setSelected(bool selected) { m_selected = selected; }
		//void setLightPosition(glm::vec3 lightPos) { m_lightPos = lightPos; }
		//void setViewPosition(glm::vec3 viewPos) { m_viewPos = viewPos; }
		//void setLightColour(glm::vec3 lightCol) { m_lightCol = lightCol; }
		inline int getObjectID() { return m_objectID; }
		inline float getObjectIDfloat() { return (float)m_objectID/(float)m_numGO; }
		inline float getObjectIDnum() { return m_numGO; }
		inline std::vector<std::shared_ptr<Component>>::iterator begin() { return m_components.begin(); }
		inline std::vector<std::shared_ptr<Component>>::iterator end() { return m_components.end(); }
	};


	class ControllerComponent : public Component
	{
	public:
		enum state { DOWN = -1, STOPPED = 0, UP = 1 };
	private:
		std::shared_ptr<Texture> m_texture;
		state m_state = UP;
	public:
		ControllerComponent() {}
		ControllerComponent(const std::shared_ptr<Texture>& texture) : m_texture(texture) {}
		inline std::shared_ptr<Texture> getTexture() { return m_texture; }
		void receiveMessage(const ComponentMessage& msg) override
		{
			switch (msg.m_msgType)
			{
			case ComponentMessageType::TextureSet:
				unsigned int texState = std::any_cast<unsigned int>(msg.m_msgData);
				m_texture->bind(texState);
				return;
			}
		}
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
		glm::vec3 getPosition() { return m_transVec; }
		glm::vec3 getRotation() { return m_rotVec; }
		glm::vec3 getScale() { return m_scaleVec; }
		glm::mat4 getModel() { calculateModel(); return m_model; }
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
				m_transVec = std::any_cast<glm::vec3>(msg.m_msgData);
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
			case ComponentMessageType::RotationSet:
			{
				m_rotVec = std::any_cast<glm::vec3>(msg.m_msgData);
				calculateModel();
				return;
			}
			case ComponentMessageType::RotationIntegrate:
			{
				glm::vec3 rotation = std::any_cast<glm::vec3>(msg.m_msgData);
				m_rotVec.x += glm::radians(rotation.x);
				m_rotVec.y += glm::radians(rotation.y);
				m_rotVec.z += glm::radians(rotation.z);
				calculateModel();
				return;
			}
			case ComponentMessageType::ScaleSet:
			{
				m_scaleVec = std::any_cast<glm::vec3>(msg.m_msgData);
				calculateModel();
				return;
			}
			case ComponentMessageType::ScaleIntegrate:
			{
				glm::vec3 scale = std::any_cast<glm::vec3>(msg.m_msgData);
				m_scaleVec.x += glm::radians(scale.x);
				m_scaleVec.y += glm::radians(scale.y);
				m_scaleVec.z += glm::radians(scale.z);
				calculateModel();
				return;
			}
			}
		}
		void onUpdate(float timestep) override
		{
			std::pair<std::string, void*> data("u_model", (void*)&m_model[0][0]);
			ComponentMessage msg(ComponentMessageType::UniformSet, data);
			sendMessage(msg);
		}
		void onAttach(GameObject* owner)override
		{
			m_owner = owner;
			std::pair<std::string, void*> data("u_model", (void*)&m_model[0][0]);
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

	class OscilateComponent : public ControllerComponent
	{
	public:
		enum state { DOWN = -1, STOPPED = 0, UP = 1 };
	private:
		float m_timeAccumulated;
		state m_state = UP;
	public:
		OscilateComponent(OscilateComponent::state initialState, float timeAccumulated):
			m_state(initialState), m_timeAccumulated(timeAccumulated) {}
			
		void onAttach(GameObject* owner) override;
		void onDetach() override;
		void onUpdate(float timestep) override;
		void onEvent(Event& e) override;
		void receiveMessage(const ComponentMessage& msg) override;
		state getState() { return m_state; };
	};
}
