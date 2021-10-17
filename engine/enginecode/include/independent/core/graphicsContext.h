/** \file OpenGLContext.h
*/
#pragma once


namespace Engine {
	/**
	\class OpenGLContext
	** \briefAdaptation of the GraphicsContext base class, implemented for OpenGL
	*/
	class GraphicsContext
	{
	public:

		virtual void init() = 0; //!< Initializing the graphics context for the API window
		virtual void swapBuffers() = 0; //!< Swap the front and back buffer (double buffering)
	private:

	};

}