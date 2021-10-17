/** \file application.h
*/
#pragma once

#include "systems/loggin.h"
#include "core/myTimer.h"
#include "core/window.h"
#include "events/eventsHeader.h"
#include "core/inputPoller.h"

namespace Engine {

	/**
	\class Application
	** \brief Fundemental class of the engine. A singleton which runs the game loop infinitely.
	*/

	class Application
	{
	protected:
		Application(); //!< Constructor

		std::shared_ptr<Log> m_logSystem;	//!<Log system
		std::shared_ptr<Window> m_window;	//!< Window
		std::shared_ptr<Timer> m_timer;		//!< Timer
		std::shared_ptr<System> m_windowSystem; //!< System for the windows
		EventHandler m_handler;		//!< An event handler

		bool onResize(WindowResizeEvent& e);	//!<Run when windows is being resized
		bool onClose(WindowCloseEvent& e);		//!<Run when window closes
		bool onFocus(WindowFocusEvent& e);		//!<Run when window gain focus
		bool onWindowMoved(WindowMovedEvent& e); //!<Run when window is moved
		bool onLostFocus(WindowLostFocusEvent& e);		//!<Run when window gain focus

		bool onKeyPressed(KeyPressedEvent& e);	//!<Run when key on keyboard is pressed
		bool onKeyReleased(KeyReleasedEvent& e);	//!<Run when key on keyboard is released

		bool onMouseMoved(MouseMovedEvent& e);	//!<Run when mouse is moved
		bool onButtonPressed(MousePressedButtonEvent& e); //!<Run when you click mouse button
		bool onButtonReleased(MouseReleasedButtonEvent& e); //!<Run when you release mouse button
		bool onScroll(MouseScrolledEvent& e); //!< Run when you scroll 
		

	private:
		static Application* s_instance; //!< Singleton instance of the application
		bool m_running = true; //!< Is the application running?

	public:
		virtual ~Application(); //!< Deconstructor
		inline static Application& getInstance() { return *s_instance; } //!< Instance getter from singleton pattern
		void run(); //!< Main loop

	};

	// To be defined in users code
	Application* startApplication(); //!< Function definition which provides an entry hook
}