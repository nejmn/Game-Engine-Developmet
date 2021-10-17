#pragma once
/** \file events.h */

#include <inttypes.h>

namespace Engine 
{
	/** \enum Event type
	** \brief An enum for event types */

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};
	/** \enum Event category 
	** \brief Enum for type category flags
	*/
	enum EventCategory
	{
		None = 0,
		EventCategoryWindow = 1 << 0,		//00000001
		EventCategoryInput = 1 << 1,		//00000010
		EventCategoryKeyboard = 1 << 2,		//00000100
		EventCategoryMouse = 1 << 3,		//00001000
		EventCategoryMouseButton = 1 << 4	//00010000
	};

	/**
	*	\class Event
	** \brief Provides a base class for an events
	*/
	class Event
	{

	public:
		virtual EventType getEventType() const = 0; //!< Get the event type
		virtual int32_t getCategoryFlags() const = 0; //!< Get the event category
		inline bool handled() const { return m_handled; } //!< Has the event been handled
		inline void handle(bool IsHandle) { IsHandle = m_handled; } //!< handle the event
		inline bool isInCategory(EventCategory category) { return getCategoryFlags() & category; } //!< Is this event in the category

	protected:
		bool m_handled = false; //!< Has the event been handled
	};
}