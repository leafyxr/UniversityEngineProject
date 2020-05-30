/** \file Camera.cpp
*/
#include "engine_pch.h"
#include "Renderer\Camera.h"
#include "systems\InputPoller.h"
#include "systems\log.h"

namespace Engine {



	void OrthographicCamera2D::updateView()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation), glm::vec3(0, 0, 1));
		m_view = glm::inverse(transform);
		m_viewProjection = m_projection * m_view;
	}

	OrthographicCamera2D::OrthographicCamera2D(float left, float right, float bottom, float top)
	{
		m_projection = glm::ortho(left, right, bottom, top);
		m_view = glm::mat4(1.0f);
		m_viewProjection = m_projection * m_view;
	}

	void OrthographicCamera2D::reset(float left, float right, float bottom, float top)
	{
		m_projection = glm::ortho(left, right, bottom, top);
		m_viewProjection = m_projection * m_view;
	}

	void PerspectiveCamera3D::updateView()
	{
		
		m_viewProjection = m_projection * m_view;
	}

	PerspectiveCamera3D::PerspectiveCamera3D(float fov, float aspectRatio, float nearClip, float farClip)
	{
		m_projection = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
		m_view = glm::mat4(1.0f);
		m_viewProjection = m_projection * m_view;
	}

	void PerspectiveCamera3D::reset(float fov, float aspectRatio, float nearClip, float farClip)
	{
		m_projection = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
		m_view = glm::mat4(1.0f);
		m_viewProjection = m_projection * m_view;
	}

	FreeOrthoCameraController2D::FreeOrthoCameraController2D()
	{
	}

	void FreeOrthoCameraController2D::init(float left, float right , float bottom, float top)
	{
		m_AspectRatio = right/top;
		m_ZoomLevel = 1.0f;
		m_camera = std::shared_ptr<OrthographicCamera2D>(new OrthographicCamera2D(left, right, bottom, top));
	}

	void FreeOrthoCameraController2D::onUpdate(float timestep)
	{
		if (InputPoller::isKeyPressed(KEY_Q)) {
			m_rotation -= timestep * m_rotateSpeed;
			if (m_rotation > 180.f) m_rotation -= 360.f;
			else if (m_rotation <= -180.f) m_rotation += 360.f;
		}
		if (InputPoller::isKeyPressed(KEY_E)) {
			m_rotation += timestep * m_rotateSpeed;
			if (m_rotation > 180.f) m_rotation -= 360.f;
			else if (m_rotation <= -180.f) m_rotation += 360.f;
		}
		m_camera->setRotation(m_rotation);
	}

	bool FreeOrthoCameraController2D::onResize(WindowResizeEvent& e)
	{
		return false;
	}

	void FPSCameraControllerEuler::updateView()
	{
		glm::vec3 forward;
		forward.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		forward.y = sin(glm::radians(m_pitch));
		forward.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		m_front = forward;

		m_right = glm::normalize(glm::cross(m_front, m_worldUp));
		m_up = glm::normalize(glm::cross(m_right, m_front));

		m_view = glm::lookAt(m_position, m_position + m_front, m_up);

		m_camera->setView(m_view);
	}

	FPSCameraControllerEuler::FPSCameraControllerEuler()
	{
		
	}

	void FPSCameraControllerEuler::init(float fov, float aspectRatio, float nearClip, float farClip)  
	{
		m_nearPlane = nearClip;
		m_farPlane = farClip;
		m_aspectRatio = aspectRatio;
		m_FOV = fov;
		m_camera = std::shared_ptr<PerspectiveCamera3D>(new PerspectiveCamera3D(fov, aspectRatio, nearClip, farClip));
		m_front = glm::vec3(0.0f, 0.0f, -1.0f);
		m_worldUp = glm::vec3(0.f, 1.0f, 0.f);
		m_view = m_camera->getView();
		m_position = m_camera->getPosition();
		m_yaw = -90.0f;
		m_pitch = 0;
		updateView();
	}

	void FPSCameraControllerEuler::onUpdate(float timestep)
	{
		if (InputPoller::isKeyPressed(KEY_W)) { m_position += m_front * m_translationSpeed * timestep; }
		if (InputPoller::isKeyPressed(KEY_S)) { m_position -= m_front * m_translationSpeed * timestep; }
		if (InputPoller::isKeyPressed(KEY_A)) { m_position -= m_right * m_translationSpeed * timestep; }
		if (InputPoller::isKeyPressed(KEY_D)) { m_position += m_right * m_translationSpeed * timestep; }
		if (InputPoller::isKeyPressed(KEY_SPACE)) { m_position += m_up * m_translationSpeed * timestep; }
		if (InputPoller::isKeyPressed(KEY_LEFT_SHIFT)) { m_position -= m_up * m_translationSpeed * timestep;	}
		if (InputPoller::isMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
			glm::vec2 currentMousePosition = InputPoller::getMousePosition();
			glm::vec2 mouseDelta = currentMousePosition - m_lastMousePosition;

			float sum = mouseDelta.x * m_rotationSpeed * timestep;
			m_yaw += mouseDelta.x * m_rotationSpeed * timestep;
			m_pitch -= mouseDelta.y * m_rotationSpeed * timestep;

			if (m_pitch > 89.0f)
				m_pitch = 89.0f;
			if (m_pitch < -89.0f)
				m_pitch = -89.0f;
			
		}
		m_lastMousePosition = InputPoller::getMousePosition(); 
		updateView();
		m_camera->setPosition(m_position);
	}

	void FPSCameraControllerEuler::onEvent(Event & e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<MouseButtonPressedEvent>(std::bind(&FPSCameraControllerEuler::onMouseButtonPressed, this, std::placeholders::_1));
		dispatcher.dispatch<MouseButtonReleasedEvent>(std::bind(&FPSCameraControllerEuler::onMouseButtonReleased, this, std::placeholders::_1));
		dispatcher.dispatch<WindowResizeEvent>(std::bind(&FPSCameraControllerEuler::onResize, this, std::placeholders::_1));
	}

	bool FPSCameraControllerEuler::onMouseButtonPressed(MouseButtonPressedEvent & e)
	{
		if (e.getMouseButton() == MOUSE_BUTTON_LEFT)
			m_lastMousePosition = InputPoller::getMousePosition();
		return false;
	}

	bool FPSCameraControllerEuler::onMouseButtonReleased(MouseButtonReleasedEvent & e)
	{
		if (e.getMouseButton() == MOUSE_BUTTON_LEFT)
			 m_lastMousePosition = InputPoller::getMousePosition();
		return false;
	}

	bool FPSCameraControllerEuler::onResize(WindowResizeEvent & e)
	{
		NG_INFO("Resize Camera");
		m_aspectRatio = (float)e.getWidth() / (float)e.getHeight();
		m_camera->reset(m_FOV,m_aspectRatio, m_nearPlane, m_farPlane);
		return false;
	}

}