/** \file window.h
*/
#pragma once

#include "systems/loggin.h"
#include "events/eventsHeader.h"
#include "events/eventsHandler.h"
#include "core/graphicsContext.h"

namespace Engine {


	struct WindowProperties //!< Window Properties struct, holding things like the title, width, height and isFullScreen and isVsync
	{
		char * title;
		uint32_t width;
		uint32_t height;
		bool isFullScreen;
		bool isVSync;

		WindowProperties(char * title = "Sample text", uint32_t width = 800, uint32_t height = 600, bool fullscreen = false) : title(title), width(width), height(height), isFullScreen(fullscreen) {}
	};
	/**
	** \brief Pure Virtual Class for interface purposes
	*/
	class Window
	{
	public:

		virtual void init(const WindowProperties& properties) = 0; //!<Initialise the window
		virtual void close() = 0;
		virtual ~Window() {};
		virtual void onUpdate(float timestep) = 0;
		virtual void setVSync(bool VSync) = 0;
		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;
		virtual void* getNativeWindow() const = 0;
		virtual bool isFullScreenMode() const = 0;
		virtual bool isVSync() const = 0; //!<Sync the framerate with the screen refresh rate

		inline EventHandler& getEventHandler() { return m_handler; }

		static Window* Create(const WindowProperties& properties = WindowProperties());
	protected:
		std::shared_ptr<GraphicsContext> m_graphicsContext;
		EventHandler m_handler; //!<Event handler
	};
}
