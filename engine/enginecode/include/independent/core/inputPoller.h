/* \file inputPoller.h*/
#pragma once
#include <glm/glm.hpp>

namespace Engine 
{
	/**\class inputPoller
	** \brief API input poller for getting the state from keyboard and mouse
	*/
	class InputPoller
	{
	public:
		static bool isKeyPressed(int32_t keyCode); //!< Is the key pressed?
		static bool isMouseButtonPressed(int32_t mouseButton); //!<Is the mouse button pressed?
		static glm::vec2 getMousePosition(); //!< mouse positon at the time

		static void setNativeWindow(void* nativeWin);
		inline static float getMousePosX() { return getMousePosition().x; }
		inline static float getMousePosY() { return getMousePosition().y; }
	};
}

