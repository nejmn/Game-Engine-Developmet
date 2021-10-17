/** \file mouseEvent.h
*/
#pragma once
#include "events.h"
#include <glm/glm.hpp>

namespace Engine
{
	/**
	\class mouseEvent
	\* brief base class for mouse events
	*/

	class MouseEvent : public Event
	{
		virtual inline int32_t getCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }
	};

	/**
	\class MouseMovedEvent
	*\brief Mouse moved event 
	*/
	class MouseMovedEvent : public MouseEvent
	{
	public:
		MouseMovedEvent(float x, float y) : m_moveX(x), m_moveY(y) {}

		static EventType getStaticType() { return EventType::MouseMoved; } //!<Return static type
		virtual inline EventType getEventType() const override { return getStaticType();} //!< Get the event type

		inline float getPosX() const { return m_moveY; }	//!<Getting X position of the cursor
		inline float getPosY() const { return m_moveY; }	//!<Getting Y position of the cursor
		inline glm::vec2 getPos() const { return glm::vec2(m_moveY, m_moveY); } //!< Get the 2 dimensional vector for the mouse cursor

	private:
		float m_moveX, m_moveY;
	};

/**
\class MosueScrolledEvent
*\ brief Scroll used event
*/
	class MouseScrolledEvent : public MouseEvent
	{
	public:
		MouseScrolledEvent(float xOff, float yOff) : m_xOffset(xOff), m_yOffset(yOff) {}

		static EventType getStaticType() { return EventType::MouseScrolled; } //!<Return static type
		virtual inline EventType getEventType() const override { return getStaticType();} //!< Get the event type

		inline float getPosX() const { return  m_xOffset; }	
		inline float getPosY() const { return m_yOffset; }	

	private:
		float m_xOffset, m_yOffset;
	};

/**
\class MousePressedButtonEvent

*\ brief Mouse button pressed event
*/
	class MousePressedButtonEvent : public MouseEvent
	{
	public:
		MousePressedButtonEvent(int32_t button) : m_button(button) {}

		static EventType getStaticType() { return EventType::MouseButtonPressed; } //!<Return static type
		virtual inline EventType getEventType() const override { return getStaticType(); } //!< Get the event type

		inline int32_t getButtonPressed() const { return m_button; }


	private:
		int32_t m_button;
	};

/**
\class MouseReleasedButtonEvent
*\ brief Mouse button released event
*/
	class MouseReleasedButtonEvent : public MouseEvent
	{
	public:
		MouseReleasedButtonEvent(int32_t button) : m_button(button) {}

		static EventType getStaticType() { return EventType::MouseButtonPressed; } //!<Return static type
		virtual inline EventType getEventType() const override { return getStaticType();} //!< Get the event type

		inline int32_t getButtonPressed() const { return m_button; }


	private:
		int32_t m_button;
	};
}
