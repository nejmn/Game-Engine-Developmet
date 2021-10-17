/** \file GLFWGraphicsContext.h*/

#pragma once


#include <GLFW/glfw3.h>
#include "core/graphicsContext.h"

namespace Engine
{
	/** \class GLFW_GraphicsContext
	** \brief Graphics context class
	*/
	class GLFW_GraphicsContext : public GraphicsContext
	{
	public:
		GLFW_GraphicsContext(GLFWwindow* win) : m_window(win) {}
		virtual void init() override;
		virtual void swapBuffers() override;
	private:
		GLFWwindow* m_window;
	};
}