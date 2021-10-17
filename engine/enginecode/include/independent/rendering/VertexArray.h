/* \file VertexArray.h*/
#pragma once

#include <vector>
#include <memory>

#include "rendering/VertexBuffer.h"
#include "rendering/indexBuffer.h"

namespace Engine
{
	/** \class VertexArray
	** \brief Abstraction of the vertex array for the OpenGL
	*/
	class VertexArray
	{
	public:
		virtual ~VertexArray() = default;

		virtual inline uint32_t getRenderID() const = 0;
		virtual inline uint32_t getDrawCount() const = 0;

		virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
		virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

		virtual std::vector<std::shared_ptr<VertexBuffer>> getVertexBuffer() const = 0;
		virtual std::shared_ptr<IndexBuffer> getIndexBuffer() const = 0;

		static VertexArray* create();
	};
}