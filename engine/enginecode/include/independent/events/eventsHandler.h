/** \file eventHandler.h*/

#pragma once

#include "eventsHeader.h"

#include <functional>

namespace Engine
{
	/**
	\class EventHandler
	** \brief Event handler with setters and gettets of events on callback
	*/
	class EventHandler
	{
	public: 
		//window events setters
		void setOnCloseCallback(const std::function<bool(WindowCloseEvent&)>& fn) { m_onCloseCallback = fn; }
		void setOnResizeCallback(const std::function<bool(WindowResizeEvent&)>& fn) { m_onResizeCallback = fn; }
		void setOnLostFocusCallback(const std::function<bool(WindowLostFocusEvent&)>& fn) { m_onLostFocusCallback = fn; }
		void setOnFocusCallback(const std::function<bool(WindowFocusEvent&)>& fn) { m_onFocusCallback = fn; }
		void setOnWindowMovedCallback(const std::function<bool(WindowMovedEvent&)>& fn) { m_onWindowMovedCallback = fn; }

		// keyboard events setters
		void setOnKeyPressedCallback(const std::function<bool(KeyPressedEvent&)>& fn) { m_onKeyPressedCallback = fn; }
		void setOnKeyReleasedCallback(const std::function<bool(KeyReleasedEvent&)>& fn) { m_onKeyReleasedCallback = fn; }
		void setOnKeyTypedCallback(const std::function<bool(KeyTypedEvent&)>& fn) { m_onKeyTypedCallback = fn; }
		// mouse events setters 
		void setOnButtonPressedCallback(const std::function<bool(MousePressedButtonEvent&)>& fn) { m_onButtonPressedCallback = fn; }
		void setOnButtonReleasedCallback(const std::function<bool(MouseReleasedButtonEvent&)>& fn) { m_onButtonReleasedCallback = fn; }
		void setOnMouseMovedCallback(const std::function<bool(MouseMovedEvent&)>& fn) { m_onMouseMovedCallback = fn; }
		void setOnMouseScrolledCallback(const std::function<bool(MouseScrolledEvent&)>& fn) { m_onMouseScrolledCallback = fn; }

		//window events getters
		std::function<bool(WindowCloseEvent&)>& getOnCloseCallback() { return m_onCloseCallback; }
		std::function<bool(WindowResizeEvent&)>& getOnResizeCallback() { return m_onResizeCallback; }
		std::function<bool(WindowLostFocusEvent&)>& getOnLostFocusCallback() { return m_onLostFocusCallback; }
		std::function<bool(WindowFocusEvent&)>& getOnFocusCallback() { return m_onFocusCallback; }
		std::function<bool(WindowMovedEvent&)>& getOnWindowMovedCallback() { return m_onWindowMovedCallback; }
		//Keyboard events getters
		std::function<bool(KeyPressedEvent&)>& getOnKeyPressedCallback() { return m_onKeyPressedCallback; }
		std::function<bool(KeyReleasedEvent&)>& getOnKeyReleasedCallback() { return m_onKeyReleasedCallback; }
		std::function<bool(KeyTypedEvent&)>& getOnKeyTypedCallback() { return m_onKeyTypedCallback; }
		//mouse events getters
		std::function<bool(MousePressedButtonEvent&)>& getOnButtonPressedCallback() { return m_onButtonPressedCallback; }
		std::function<bool(MouseReleasedButtonEvent&)>& getOnButtonReleasedCallback() { return m_onButtonReleasedCallback; }
		std::function<bool(MouseMovedEvent&)>& getOnMouseMovedCallback() { return m_onMouseMovedCallback; }
		std::function<bool(MouseScrolledEvent&)>& getOnMouseScrolledCallback() { return m_onMouseScrolledCallback; }
	private:
		//window events
		std::function<bool(WindowCloseEvent&)> m_onCloseCallback = std::bind(&EventHandler::defaultOnClose, this, std::placeholders::_1);
		std::function<bool(WindowResizeEvent&)> m_onResizeCallback = std::bind(&EventHandler::defaultOnResize, this, std::placeholders::_1);
		std::function<bool(WindowLostFocusEvent&)> m_onLostFocusCallback = std::bind(&EventHandler::defaultOnLostFocus, this, std::placeholders::_1);
		std::function<bool(WindowFocusEvent&)> m_onFocusCallback = std::bind(&EventHandler::defaultOnFocus, this, std::placeholders::_1);
		std::function<bool(WindowMovedEvent&)> m_onWindowMovedCallback = std::bind(&EventHandler::defaultOnWindowMoved, this, std::placeholders::_1);
		// keyboard events
		std::function<bool(KeyPressedEvent&)> m_onKeyPressedCallback = std::bind(&EventHandler::defaultOnKeyPressed, this, std::placeholders::_1);
		std::function<bool(KeyReleasedEvent&)> m_onKeyReleasedCallback = std::bind(&EventHandler::defaultOnKeyReleased, this, std::placeholders::_1);
		std::function<bool(KeyTypedEvent&)> m_onKeyTypedCallback = std::bind(&EventHandler::defaultOnKeyTyped, this, std::placeholders::_1);
		// mouse events
		std::function<bool(MousePressedButtonEvent&)> m_onButtonPressedCallback = std::bind(&EventHandler::defaultOnPressedButton, this, std::placeholders::_1);
		std::function<bool(MouseReleasedButtonEvent&)> m_onButtonReleasedCallback = std::bind(&EventHandler::defaultOnReleasedButton, this, std::placeholders::_1);
		std::function<bool(MouseMovedEvent&)> m_onMouseMovedCallback = std::bind(&EventHandler::defaultOnMouseMoved, this, std::placeholders::_1);
		std::function<bool(MouseScrolledEvent&)> m_onMouseScrolledCallback = std::bind(&EventHandler::defaultOnMouseScroll, this, std::placeholders::_1);

		//window events
		bool defaultOnClose(WindowCloseEvent& e) { return false; }
		bool defaultOnResize(WindowResizeEvent& e) { return false; }
		bool defaultOnLostFocus(WindowLostFocusEvent& e) { return false; }
		bool defaultOnFocus(WindowFocusEvent& e) { return false; }
		bool defaultOnWindowMoved(WindowMovedEvent& e) { return false; }
		// keyboard events
		bool defaultOnKeyPressed(KeyPressedEvent& e) { return false; }
		bool defaultOnKeyReleased(KeyReleasedEvent& e) { return false; }
		bool defaultOnKeyTyped(KeyTypedEvent	& e) { return false; }
		// mouse events
		bool defaultOnPressedButton(MousePressedButtonEvent& e) { return false; }
		bool defaultOnReleasedButton(MouseReleasedButtonEvent& e) { return false; }
		bool defaultOnMouseMoved(MouseMovedEvent& e) { return false; }
		bool defaultOnMouseScroll(MouseScrolledEvent& e) { return false; }
	};
}