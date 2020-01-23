/** \file WindowEvents.h
*/
#pragma once
#include "Event.h"

namespace Engine {

	/**
	\class WindowCloseEvent
	on window close
	*/
	class WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() {}
		static EventType getStaticType() { return EventType::WindowClose; }
		EventType getEventType() const override { return EventType::WindowClose; }
		int getCategoryFlags() const override { return EventCategoryWindow; }
	};

	/**
	\class WindowResizeEvent
	on Window resize
	*/
	class WindowResizeEvent : public Event {
	private:
		int m_width;
		int m_height;
	public:
		WindowResizeEvent(int width, int height) : m_width(width), m_height(height) {}

		static EventType getStaticType() { return EventType::WindowResize; }
		virtual EventType getEventType() const override { return EventType::WindowResize; }
		virtual int getCategoryFlags() const override { return EventCategoryWindow; }

		inline int getWidth() const { return m_width; }
		inline int getHeight() const { return m_height; }
	};

	/**
	\class WindowFocusEvent
	on Window Focus
	*/
	class WindowFocusEvent : public Event {
	private:
		int m_xPos;
		int m_yPos;
	public:
		WindowFocusEvent(int xPos, int yPos) : m_xPos(xPos), m_yPos(yPos) {}
		static EventType getStaticType() { return EventType::WindowFocus; }
		EventType getEventType() const override { return EventType::WindowFocus; }
		int getCategoryFlags() const override { return EventCategoryWindow; }

		inline int getXPos() { return m_xPos; }
		inline int getYPos() { return m_yPos; }
	};

	/**
	\class LostFocusEvent
	on window lost focus
	*/
	class WindowLostFocusEvent : public Event {
	private:
		int m_xPos;
		int m_yPos;
	public:
		WindowLostFocusEvent(int xPos, int yPos) : m_xPos(xPos), m_yPos(yPos) {}
		static EventType getStaticType() { return EventType::WindowLostFocus; }
		EventType getEventType() const override { return EventType::WindowLostFocus; }
		int getCategoryFlags() const override { return EventCategoryWindow; }

		inline int getXPos() { return m_xPos; }
		inline int getYPos() { return m_yPos; }
	};

	/**
	\class WindowMovedEvent
	on window moved
	*/
	class WindowMovedEvent : public Event {
	private:
		int m_xPos;
		int m_yPos;
	public:
		WindowMovedEvent(int xPos, int yPos) : m_xPos(xPos), m_yPos(yPos) {}
		static EventType getStaticType() { return EventType::WindowMoved; }
		EventType getEventType() const override { return EventType::WindowMoved; }
		int getCategoryFlags() const override { return EventCategoryWindow; }

		inline int getXPos() { return m_xPos; }
		inline int getYPos() { return m_yPos; }
	};
}