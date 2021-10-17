/* \file subTexture*/
#pragma once

#include "platform/OpenGL/OpenGLTextures.h"
#include <memory>
#include <glm/glm.hpp>

namespace Engine
{
	/** \class SubTextures
	** \brief Api agnostic index buffer
	*/
	class SubTexture
	{
	public:
		SubTexture() {};
		SubTexture(const std::shared_ptr<OpenGLTextures>& texture, const glm::vec2& UVStart, const glm::vec2& UVEnd);
		inline glm::vec2 getUVStart() { return m_UVStart; }
		inline glm::vec2 getUVEnd() { return m_UVEnd; }
		glm::ivec2 getSize() { return m_size; } //!< get size 
		glm::vec2 getSizef() { return { static_cast<float> (m_size.x), static_cast<float>(m_size.y) }; }
		inline uint32_t getWidth() { return m_size.x; } //!< get width of the texture
		inline uint32_t getHeight() { return m_size.y; } //!< get height of the texture
		inline uint32_t getWidthf() { return static_cast<float>(m_size.x); }
		inline uint32_t getHeightf() { return static_cast<float>(m_size.y); }
		float transformU(float U); 
		float transformV(float V);
		glm::vec2 transformUV(glm::vec2 UV);//!< Tranform origin to atlased co-ords
	private:
		std::shared_ptr<OpenGLTextures> m_texture;
		glm::vec2 m_UVStart;
		glm::vec2 m_UVEnd; //!< the end of
		glm::ivec2 m_size; //!<How many pixels
	};
}