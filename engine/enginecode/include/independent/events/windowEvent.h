/** \file WindowEvents.h
*/
#pragma once
#include "events.h"
#include <glm/glm.hpp>

namespace Engine
{
/**
\class WindowCloseEvent
*\brief window closed event
*/

	class WindowCloseEvent : public Event
	{
	public:
		static EventType getStaticType() { return EventType::WindowClose; } //!<Return static type
		virtual inline EventType getEventType() const override { return EventType::WindowClose; } //!< Get the event type
		virtual int32_t getCategoryFlags() const override { return EventCategoryWindow; } //!< Get the event category flags
	};

/**
\class WindowResizeEvent
*\brief window resized event
*/
	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(int32_t width, int32_t height) : m_width(width), m_height(height) {}
		static EventType getStaticType() { return EventType::WindowResize; } //!<Return static type
		virtual inline EventType getEventType() const override { return EventType::WindowResize; } //!< Get the event type
		virtual int32_t getCategoryFlags() const override { return EventCategoryWindow; } //!< Get the event category flags
	
		inline int32_t getWidth() const { return m_width; }
		inline int32_t getHeight() const { return m_height; }
		inline glm::ivec2 getSize() const { return { m_width, m_height }; }

	private:
		unsigned int m_width, m_height;
	};

/**
\class WindowMovedEvent
*\brief window change position
*/
	class WindowMovedEvent : public Event
	{
	public:
		WindowMovedEvent(int32_t x, int32_t y) : m_posX(x), m_posY(y) {}
		static EventType getStaticType() { return EventType::WindowMoved; } //!<Return static type
		virtual inline EventType getEventType() const override { return EventType::WindowMoved; } //!< Get the event type
		virtual int32_t getCategoryFlags() const override { return EventCategoryWindow; } //!< Get the event category flags

		inline int32_t getPosX() const { return m_posX; }
		inline int32_t getPosY() const { return m_posY; }
		inline glm::ivec2 getPos() const { return {m_posX, m_posY };
	}
	private:
		int32_t m_posX, m_posY;
	};

	/**
\class WindowFocusEevent
*\brief window gained focus 
*/
	class WindowFocusEvent : public Event
	{
	public:
		WindowFocusEvent() {}
		static EventType getStaticType() { return EventType::WindowFocus; } //!<Return static type
		virtual inline EventType getEventType() const override { return EventType::WindowFocus; } //!< Get the event type
		virtual int32_t getCategoryFlags() const override { return EventCategoryWindow; } //!< Get the event category flags

	};

	/**
\class WindowLostFocusEevent
\*brief window list focus
*/
	class WindowLostFocusEvent : public Event
	{
	public:
		WindowLostFocusEvent() {}
		static EventType getStaticType() { return EventType::WindowLostFocus; } //!<Return static type
		virtual inline EventType getEventType() const override { return EventType::WindowLostFocus; } //!< Get the event type
		virtual int32_t getCategoryFlags() const override { return EventCategoryWindow; } //!< Get the event category flags

	};

}