/** \file GLFWWindowImpl.h*/

#pragma once

#include "core/window.h"
#include <GLFW/glfw3.h>
#include "platform/GLFW/GLFW_GraphicsContext.h"

namespace Engine
{
	/** \class GLFWindowImpl
	* \brief Implementation of a window using the GLFW
	*/
	
	class GLFWWindowImpl : public Window
	{
	public:
		GLFWWindowImpl(const WindowProperties& properties); //!<Constructor
		virtual void init(const WindowProperties& properties) override; //!<Initialise the window
		virtual void close() override;
		virtual ~GLFWWindowImpl() {};
		virtual void onUpdate(float timestep) override;
		virtual void setVSync(bool VSync) override;
		virtual inline unsigned int getWidth() const override { return m_props.width; }
		virtual inline unsigned int getHeight() const override { return m_props.height; }
		virtual inline void* getNativeWindow() const override { return m_native; };
		virtual inline bool isFullScreenMode() const override { return m_props.isFullScreen; };
		virtual inline bool isVSync() const override { return m_props.isVSync; };; //!<Sync the framerate with the screen refresh rate

	private: 
		WindowProperties m_props; //!< Properties for the window
		GLFWwindow* m_native; //!< Native GLFW window resolution
		float m_aspectRatio; //!< Aspect ratio 
	};

}