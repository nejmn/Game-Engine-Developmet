/**\ GLFWWindowImpl.cpp*/

#include "engine_pch.h"
#include "platform/GLFW/GLFWWindowImpl.h"

#include "systems/loggin.h"

namespace Engine
{
#ifdef NG_PLATFORM_WINDOWS
	Window* Window::Create(const WindowProperties& properties)
	{
		return new GLFWWindowImpl(properties);
	}
#endif // NG_PLATFORM_WINDOWS



	GLFWWindowImpl::GLFWWindowImpl(const WindowProperties& properties)
	{
		init(properties);
	}

	void GLFWWindowImpl::init(const WindowProperties& properties)
	{
		m_props = properties;

		m_aspectRatio = static_cast<float>(m_props.width) / static_cast<float>(m_props.height);
		
		if (m_props.isFullScreen)
		{
			Log::error("Fullscreen not yet implemented");
		}
		else
		{
			m_native = glfwCreateWindow(m_props.width, m_props.height, m_props.title, nullptr, nullptr);
		}

		m_graphicsContext.reset(new GLFW_GraphicsContext(m_native));

		m_graphicsContext->init();

		glfwSetWindowUserPointer(m_native, static_cast<void*>(&m_handler));

		glfwSetWindowCloseCallback(m_native, 
			[](GLFWwindow* window)
			{
				EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));

				auto& onClose = handler->getOnCloseCallback();
				WindowCloseEvent e;
				onClose(e);
			}
			);

		glfwSetWindowFocusCallback(m_native,
			[](GLFWwindow* window, int state)
			{
				EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));

				if (state == GLFW_TRUE) //focus gained
				{
					auto& onFocus = handler->getOnFocusCallback();
					WindowFocusEvent e;
					onFocus(e);
				}
				else if (state == GLFW_FALSE) //focus lost
				{
					auto& onLostFocus = handler->getOnLostFocusCallback();
					WindowLostFocusEvent e;
					onLostFocus(e);
				}
			}
		);
		

		glfwSetWindowSizeCallback(m_native, 
			[](GLFWwindow*window, int newWidth, int newHeight)
			{
				EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
				auto& onResize = handler->getOnResizeCallback();
				
				WindowResizeEvent e(newWidth, newHeight);
				onResize(e);
			}
			);



		glfwSetWindowPosCallback(m_native,
			[](GLFWwindow* window, int posX, int posY)
			{
				EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
				auto& onWindowMoved = handler->getOnWindowMovedCallback();

				WindowMovedEvent e(posX, posY);
				onWindowMoved(e);
			}
		);

		glfwSetKeyCallback(m_native,
			[](GLFWwindow* window, int keyCode, int scanCode, int action, int mods)
			{
				EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));

				if (action == GLFW_PRESS)
				{
					auto& onKeyPress = handler->getOnKeyPressedCallback();
					KeyPressedEvent e(keyCode, 0);
					onKeyPress(e);
				}
				else if (action == GLFW_REPEAT)
				{
					auto& onKeyPress = handler->getOnKeyPressedCallback();
					KeyPressedEvent e(keyCode, 1);
					onKeyPress(e);
				}
				else if (action == GLFW_RELEASE)
				{
					auto& onKeyRelease = handler->getOnKeyReleasedCallback();
					KeyReleasedEvent e(keyCode);
					onKeyRelease(e);
				}

			}
		);

		glfwSetCursorPosCallback(m_native,
			[](GLFWwindow* window, double mouseX, double mouseY)
			{
				MouseMovedEvent e(static_cast<float>(mouseX), static_cast<float>(mouseY));
				EventHandler* handler = (EventHandler*)glfwGetWindowUserPointer(window);
				auto& onMouseMoved = handler->getOnMouseMovedCallback();
				onMouseMoved(e);
			}
		);

		glfwSetScrollCallback(m_native,
			[](GLFWwindow* window, double xOffset, double yOffset)
			{
				MouseScrolledEvent e(static_cast<float>(xOffset), static_cast<float>(yOffset));

				EventHandler* handler = (EventHandler*)glfwGetWindowUserPointer(window);
				auto& onScroll = handler->getOnMouseScrolledCallback();
				onScroll(e);
			}
		);

		glfwSetMouseButtonCallback(m_native,
			[](GLFWwindow* window, int button, int action, int mods)
			{
			
				EventHandler* handler = (EventHandler*)glfwGetWindowUserPointer(window);

				if (action == GLFW_PRESS) //mouse button pressed
				{
					MousePressedButtonEvent e(button);
					auto& onButtonPressed = handler->getOnButtonPressedCallback();
					onButtonPressed(e);
				}
				else if (action == GLFW_RELEASE) //mouse button released
				{
					MouseReleasedButtonEvent e(button);
					auto& onButtonReleased = handler->getOnButtonReleasedCallback();
					onButtonReleased(e);
				}

			}
		);

	}

	void GLFWWindowImpl::close()
	{
		glfwDestroyWindow(m_native);
	}

	void GLFWWindowImpl::onUpdate(float timestep)
	{
		glfwPollEvents();
		m_graphicsContext->swapBuffers();
	}

	void GLFWWindowImpl::setVSync(bool VSync)
	{
		m_props.isVSync = VSync;
		if (m_props.isVSync) { glfwSwapInterval(1); }
		else {glfwSwapInterval(0);}
	}

}