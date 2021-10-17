/* \file OpenGLVertexBuffer*/

#pragma once

#include "rendering/bufferLayout.h"
#include "rendering/VertexBuffer.h"

namespace Engine
{
	/** \class OpenGLVertexBuffer
	*\brief Vertex buffer class with OpenGL abstraction
	*/
	class OpenGLVertexBuffer: public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(void* vertices, uint32_t size, BufferLayout layout);
		virtual ~OpenGLVertexBuffer();
		virtual void edit(void* vertices, uint32_t size, uint32_t offset);
		virtual inline uint32_t getRenderID() const override { return m_OpenGL_ID; }
		virtual inline const BufferLayout& getLayout() const override { return m_layout; }
	private:
		uint32_t m_OpenGL_ID; //!< Render ID
		BufferLayout m_layout; 
	};
}