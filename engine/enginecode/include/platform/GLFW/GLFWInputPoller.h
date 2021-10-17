/** \file GLFWinputPoller.h*/
#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

namespace Engine
{

	/* \class GLFWSystem
	*\brief Input poller to get current state from keyboard and moude that is transfered to GLFW system
	*/

	class GLFWInputPoller
	{
	public:
		static bool isKeyPressed(int32_t keyCode); //!<Is the key pressed
		static bool isMouseButtonPressed(int32_t mouseButton); //!< Is mouse button pressed?
		static glm::vec2 getMousePosition(); //!< Cursor position
		static void setCurrentWindow(GLFWwindow* newWin) { s_window = newWin; }
	private:
		static GLFWwindow* s_window; //!< Current GLFW window
	};
}