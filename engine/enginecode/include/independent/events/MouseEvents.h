/** \file MouseEvents.h
*/
#pragma once
#include "Event.h"

namespace Engine {

	/**
	\class MouseButtonEvent
	mouse events
	*/
	class MouseButtonEvent : public Event {
	protected:
		int m_Button;
		MouseButtonEvent(int button) : m_Button(button){}
	public:
		virtual int getCategoryFlags() const override { return EventCategoryMouse | EventCategoryMouseButton | EventCategoryInput; }

		inline int getMouseButton() { return m_Button; }
	};

	/**
	\class MouseButtonPressedEvent
	mouse button press
	*/
	class MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(int button): MouseButtonEvent(button){}

		static EventType getStaticType() { return EventType::MouseButtonPressed; }
		virtual EventType getEventType() const override { return EventType::MouseButtonPressed; }
	};

	/**
	\class MouseButtonReleasedEvent
	mouse button released
	*/
	class MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

		static EventType getStaticType() { return EventType::MouseButtonReleased; }
		virtual EventType getEventType() const override { return EventType::MouseButtonReleased; }
	};

	/**
	\class MouseMovedEvent
	mouse button moved
	*/
	class MouseMovedEvent : public Event {
	private:
		int m_xOffset;
		int m_yOffset;
	public:
		MouseMovedEvent(int xOffset, int yOffset) : m_xOffset(xOffset), m_yOffset(yOffset){}

		static EventType getStaticType() { return EventType::MouseMoved; }
		EventType getEventType() const override { return EventType::MouseMoved; }
		int getCategoryFlags() const override { return EventCategoryMouse; }

		inline int getXOffset() { return m_xOffset; }
		inline int getYOffset() { return m_yOffset; }
	};

	/**
	\class MouseScrolledEvent
	mouse scrolled
	*/
	class MouseScrolledEvent : public Event {
	private:
		int m_xOffset;
		int m_yOffset;
	public:
		MouseScrolledEvent(int xOffset, int yOffset) : m_xOffset(xOffset), m_yOffset(yOffset) {}

		static EventType getStaticType() { return EventType::MouseScrolled; }
		EventType getEventType() const override { return EventType::MouseScrolled; }
		int getCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }

		inline int getXOffset() { return m_xOffset; }
		inline int getYOffset() { return m_yOffset; }
	};

}
