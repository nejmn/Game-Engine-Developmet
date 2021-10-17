/**\file GLFWWindows.h */

#include "systems/system.h"
#include "systems/loggin.h"
#include <GLFW/glfw3.h>

	/** \class GLFWSystem
	*\brief Implementation of a window system using the GLFW
	*/

#pragma once

namespace Engine 
{
	class GLFWSystem : public System
	{
		virtual void start(SystemSignal init = SystemSignal::None, ...) override //!<Start the system
		{
			auto errorCode = glfwInit();
			if (!errorCode) {
				Log::error("Cannot init GLFW {0}", errorCode);
			}

		}
		virtual void stop(SystemSignal init = SystemSignal::None, ...) override //!<Start the system
		{
			glfwTerminate();
		}
	};

}
