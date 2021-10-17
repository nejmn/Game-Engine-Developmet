/* \file VertexBuffer.h*/
#pragma once

#include "rendering/BufferLayout.h"

namespace Engine
{
	/** \class VertexBuffer
	** \brief Abstraction of the vertex buffer for the OpenGL
	*/
	class VertexBuffer
	{
	public:
		~VertexBuffer() = default;
		//void edit(void* vertices, uint32_t size, uint32_t offset);
		virtual inline uint32_t getRenderID() const = 0;
		virtual inline const BufferLayout& getLayout() const = 0;

		static VertexBuffer* create(void* vertices, uint32_t size, BufferLayout layout);
	};
}