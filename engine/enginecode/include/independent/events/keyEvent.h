/* \file KeyboardEvents.h */

#pragma once

#include "events.h"

namespace Engine {

	/**\class KeyEvents
	* \brief Implementation of the key events base class
	*/
	class KeyEvent : public Event
	{
	public: 

		inline int32_t getKeyCode() const { return m_keyCode; }
		virtual inline int32_t getCategoryFlags() const override { return EventCategoryKeyboard | EventCategoryInput; } //!< Get the event type

	protected:
		KeyEvent(int32_t keyCode) : m_keyCode(keyCode) {}
		int32_t m_keyCode;
	};

	/**\class KeyPressedEvent
	* \brief Implementation of the key pressed on keyboard class
	*/
	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int32_t keycode, int32_t repeatCount) : KeyEvent(keycode), m_repeatCount(repeatCount) {}
		
		static EventType getStaticType() { return EventType::KeyPressed; } //!<Return static type
		inline int32_t getRepeatCount() const { return m_repeatCount; }
		virtual inline EventType getEventType() const override { return getStaticType(); }
	private:
		int32_t m_repeatCount;
	};

	/**\class KeyReleasedEvent
	* \brief Implementation of the key released on keyboard class
	*/
	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int32_t keycode) : KeyEvent(keycode) {}

		static EventType getStaticType() { return EventType::KeyReleased; } //!<Return static type
		virtual inline EventType getEventType() const override { return getStaticType(); }

	};

	/**\class KeyTypedEvent
	* \brief Implementation of the key typed on keyboard class
	*/
	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int32_t keycode) : KeyEvent(keycode) {}

		static EventType getStaticType() { return EventType::KeyTyped; } //!<Return static type
		virtual inline EventType getEventType() const override { return getStaticType(); }

	};

}