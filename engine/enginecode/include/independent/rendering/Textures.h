/* \file Textures.h*/

#pragma once

#include <cstdint>
namespace Engine
{
	/** \class Texture
	** \brief Abstraction of the texture for the OpenGL
	*/
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual inline uint32_t getID() const = 0; //!< get the render ID
		virtual inline uint32_t getWidth() const = 0; //!< get width of the texture
		virtual inline uint32_t getHeight() const = 0; //!< get height of the texture
		virtual inline uint32_t getChannels() const = 0; //!< get channel number
		virtual inline uint32_t getWidthf() const = 0; 
		virtual inline uint32_t getHeightf() const = 0;

		static Texture* create(const char* filepath);
		static Texture* create2(uint32_t width, uint32_t height, uint32_t channels, unsigned char* data);
	};
}