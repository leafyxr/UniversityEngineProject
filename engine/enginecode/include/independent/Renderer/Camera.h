/** \file Camera.h
*/
#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\quaternion.hpp>
#include <memory>
#include <events\Event.h>
#include <events\MouseEvents.h>
#include <events\WindowEvents.h>

namespace Engine {

	//*********** Camera ******************************************
	//*************************************************************

	/**
	\class Camera
	Base Class for Camera Objects
	*/
	class Camera {
	protected:
		glm::mat4 m_projection;//!<Projection matrix
		glm::mat4 m_view;//!<View matrix
		glm::mat4 m_viewProjection;//!<View Projection Matrix
	public:
		//! Update View
		virtual void updateView() = 0;
		//! get projection
		/*!
		\return projection
		*/
		const glm::mat4& getProjection() { return m_projection; }
		//! get view
		/*!
		\return view
		*/
		const glm::mat4& getView() { return m_view; }
		//! get view projection matrix
		/*!
		\return view projection matrix
		*/
		const glm::mat4& getViewProjection() { return m_viewProjection; }
	};

	/**
	\class OrthographicCamera2D
	Implementation of a 2D Orthographic Camera
	*/
	class OrthographicCamera2D : public Camera {
	private:
		glm::vec3 m_position = glm::vec3(0.f);//!<Postion
		float m_rotation = 0.f;//!<Rotation
		//! Update View
		void updateView() override;
	public:
		//! Constuctor
		/*!
		\param left
		\param height
		\param bottom
		\param top
		*/
		OrthographicCamera2D(float left, float right, float bottom, float top);
		//! Reset
		/*!
		\param left
		\param height
		\param bottom
		\param top
		*/
		void reset(float left, float right, float bottom, float top);
		//! get position
		/*!
		\return position
		*/
		inline glm::vec3 getPosition() { return m_position; }
		//! get rotation
		/*!
		\return rotation
		*/
		inline float getRotation() const { return m_rotation; }
		//! set position
		/*!
		\param position
		*/
		void setPosition(const glm::vec3& position) { m_position = position; updateView(); }
		//! set rotation
		/*!
		\param rotation
		*/
		void setRotation(const float rotation) { m_rotation = rotation; updateView(); }
		//! set rotation and postion
		/*!
		\param position
		\param rotation
		*/
		void setPositionRotation(const glm::vec3& position, const float rotation) { m_position = position; m_rotation = rotation; updateView(); }
	};

	/**
	\class PerspectiveCamera3D
	Implementation of a 3D perspective Camera
	*/
	class PerspectiveCamera3D : public Camera {
	private:
		glm::vec3 m_position = glm::vec3(0.f);//!<Position
		glm::quat m_orientation;//!<Orientation
		//! Update View
		void updateView() override;
	public:
		//! Constuctor
		/*!
		\param fov
		\param aspectRatio
		\param nearClip
		\param farClip
		*/
		PerspectiveCamera3D(float fov, float aspectRatio, float nearClip, float farClip);
		//! Reset Camera
		/*!
		\param fov
		\param aspectRatio
		\param nearClip
		\param farClip
		*/
		void reset(float fov, float aspectRatio, float nearClip, float farClip);
		//! get position
		/*!
		\return position
		*/
		inline glm::vec3 getPosition() { return m_position; }
		//! get orientation
		/*!
		\return orientation
		*/
		inline glm::quat getOrientation() { return m_orientation; }
		//! set View
		/*!
		\param View matrix
		*/
		void setView(const glm::mat4& view) { m_view = view, m_viewProjection = m_projection * m_view; }
		//! set position
		/*!
		\param position
		*/
		void setPosition(const glm::vec3& position) { m_position = position; updateView(); }
		//! set orientation
		/*!
		\param orientation
		*/
		void setOrientation(const glm::quat& orientation) { m_orientation = orientation; updateView(); }
		//! set rotation and orientation
		/*!
		\param position
		\param orientation
		*/
		void setPositionOrientation(const glm::vec3& position, const glm::quat& orientation) { m_position = position; m_orientation = orientation; updateView(); }
	};

	//*********** Camera Controller *******************************
	//*************************************************************

	/**
	\class CameraController
	Base class for a Camera Controller
	*/
	class CameraController {
	public:
		//! Initialiser
		/*!
		\param TBD
		\param TBD
		\param TBD
		\param TBD
		*/
		virtual void init(float, float, float, float) = 0;
		virtual std::shared_ptr<Camera> getCamera() = 0;
		virtual void onUpdate(float timestep) = 0;
		virtual void onEvent(Event& e) = 0;
		virtual bool onResize(WindowResizeEvent & e) = 0;
		virtual glm::vec3 getPosition() = 0;
		virtual void setPosition(const glm::vec3& position) = 0;
	};

	/**
	\class FreeOrthoCameraController2D
	Controller for the 2D Orthographic Camera
	*/
	class FreeOrthoCameraController2D : public CameraController {
	private:
		std::shared_ptr<OrthographicCamera2D> m_camera;//!<Linked camera object
		glm::vec3 m_position = glm::vec3(0.f);//!<position
		float m_rotation = 0.f;//!<rotation
		float m_translateSpeed = 100.f;//!<move speed
		float m_rotateSpeed = 10.f;//!<rotate speed
		float m_AspectRatio;
		float m_ZoomLevel;
	public:
		FreeOrthoCameraController2D();
		//! Initializer
		/*!
		\param left
		\param top
		\param width
		\param height
		*/
		void init(float left, float right, float bottom, float top) override;
		std::shared_ptr<Camera> getCamera() override { return m_camera; }
		void onUpdate(float timestep) override;
		void onEvent(Event& e) override {};

		inline glm::vec3 getPosition() override { return glm::vec3(m_camera->getPosition()); }
		void setPosition(const glm::vec3& position) override { m_position = position; m_camera->setPosition(position); }

		bool onResize(WindowResizeEvent & e) override;

	};

	/**
	\class FPSCameraControllerEuler
	Controller for the 3D Perspective Camera, uses Euler.
	*/
	class FPSCameraControllerEuler : public CameraController {
	private:
		std::shared_ptr<PerspectiveCamera3D> m_camera;//!<Linked Camera Object
		glm::mat4 m_view;//!< View Matrix
		glm::vec3 m_position;//!< Position
		glm::vec3 m_front;//!< Camera Front direction
		glm::vec3 m_up;//!< Camera Up Direction
		glm::vec3 m_right;//!< Camera Down Direction
		glm::vec3 m_worldUp;//!< World Up
		float m_yaw;//!< Yaw rotation
		float m_pitch;//!< Pitch rotation
		float m_translationSpeed = 2.0f;//!< Move speed
		float m_rotationSpeed = 5.f;//!< rotate speed
		float m_aspectRatio, m_nearPlane, m_farPlane, m_FOV;
		glm::vec2 m_lastMousePosition;//!< last mouse position
		//! Update View
		void updateView();
	public:
		FPSCameraControllerEuler();
		//! Constuctor
		/*!
		\param fov
		\param aspect ratio
		\param near clip
		\param far clip
		*/
		void init(float fov = 45.f, float aspectRatio = 4.0f / 3.0f, float nearClip = 0.1f, float farClip = 100.f) override;
		std::shared_ptr<Camera> getCamera() override { return m_camera; }
		void onUpdate(float timestep) override;
		void onEvent(Event& e) override;
		bool onMouseButtonPressed(MouseButtonPressedEvent& e);
		bool onMouseButtonReleased(MouseButtonReleasedEvent& e);

		inline glm::vec3 getPosition() override { return m_camera->getPosition(); }
		void setPosition(const glm::vec3& position) override { m_position = position; m_camera->setPosition(position); updateView(); }

		bool onResize(WindowResizeEvent & e) override;

	};
}