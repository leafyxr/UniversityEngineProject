/** \file KeyEvents.h
*/
#pragma once
#include "Event.h"

namespace Engine {

	/**
	\class KeyEvent
	key event
	*/
	class KeyEvent : public Event {
	protected:
		int m_keycode;
		KeyEvent(int keycode) : m_keycode(keycode){}
	public:
		virtual int getCategoryFlags() const override { return EventCategoryKeyboard | EventCategoryInput; }

		inline int getKeycode() const { return m_keycode; }
	};

	/**
	\class KeyPressedEvent
	on key pressed/held
	*/
	class KeyPressedEvent : public KeyEvent {
	private:
		int m_repeatcount;
	public:
		KeyPressedEvent(int keycode, int repeatcount) : KeyEvent(keycode), m_repeatcount(repeatcount) {}

		static EventType getStaticType() { return EventType::KeyPressed; }
		virtual EventType getEventType() const override { return EventType::KeyPressed; }

		inline int getRepeatCount() const { return m_repeatcount; }
	};

	/**
	\class KeyReleasedEvent
	on key release
	*/
	class KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

		static EventType getStaticType() { return EventType::KeyReleased; }
		virtual EventType getEventType() const override { return EventType::KeyReleased; }
	};

	/**
	\class KeyTypedEvent
	on Key Type
	*/
	class KeyTypedEvent : public KeyEvent {
	public:
		KeyTypedEvent(int keycode) : KeyEvent(keycode) {}

		static EventType getStaticType() { return EventType::KeyTyped; }
		virtual EventType getEventType() const override { return EventType::KeyTyped; }
	};

}