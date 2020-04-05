#pragma once

#include "Events.h"
#include "wspch.h"

namespace Weasel {

	class WS_API KeyEvent : public Event
	{
	public:
		KeyEvent(int keycode) : m_KeyCode(keycode) {}

		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:

		int m_KeyCode;
	};

	class WS_API KeyPressedEvent : public KeyEvent
	{

	public:
		KeyPressedEvent(int keycode, int repeatCount) : KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << "(" << m_RepeatCount << "repeats) \n";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int m_RepeatCount;

	};

	class WS_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvents: " << m_KeyCode << "\n";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased);

	};

	class WS_API KeyTypedEvent : public KeyEvent
	{

	public:
		KeyTypedEvent(int keycode) : KeyEvent(keycode) {}


		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode << "\n";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)

	};

}
