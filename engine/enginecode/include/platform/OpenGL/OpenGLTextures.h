/** \file OpenGLTextures.h
*Abstraction for the textures using the OpenGL
*/

#pragma once

#include "rendering/Textures.h"

namespace Engine
{
	/** \class OpenGLTextures
	* \brief Textures OpenGL abstract 
	*/
	class OpenGLTextures : public Texture
	{
	public:
		OpenGLTextures(const char * filepath);
		OpenGLTextures(uint32_t width, uint32_t height, uint32_t channels, unsigned char * data);
		~OpenGLTextures();
		void edit(uint32_t xOffset, uint32_t yOffset, uint32_t width, uint32_t height, unsigned char* data);
		inline uint32_t getID()	const override{ return m_OpenGL_ID; }
		inline uint32_t getWidth()	const override{ return m_width; }
		inline uint32_t getHeight()	const override{ return m_height; }
		inline uint32_t getWidthf()	const override{ return static_cast<float>( m_width); }
		inline uint32_t getHeightf() const override{ return static_cast<float>( m_height); }
		inline uint32_t getChannels() const override{ return m_channels; }
	private:
		uint32_t m_OpenGL_ID;
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_channels;
		void init(uint32_t width, uint32_t height, uint32_t channels, unsigned char * data);
	};

}