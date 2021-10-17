/** \file OpenGLVertexArray.h
*/

#pragma once

#include <vector>
#include <memory>
#include "platform/OpenGL/OpenGLVertexBuffer.h"
#include "platform/OpenGL/OpenGLIndexBuffer.h"
#include "rendering/VertexArray.h"

namespace Engine
{
	/** \class OpenGLVertexArray
	* \brief Vertex array class with OpenGL abstraction
	*/
	class OpenGLVertexArray :public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;
		virtual inline uint32_t getRenderID() const override { return m_OpenGL_ID; }
		virtual inline uint32_t getDrawCount() const override {if (m_indexBuffer) { return m_indexBuffer->getCount(); }else { return 0; }};
		
		std::vector<std::shared_ptr<VertexBuffer>> getVertexBuffer() const override;
		std::shared_ptr<IndexBuffer> getIndexBuffer() const override;

	private:
		uint32_t m_OpenGL_ID; //!< Render ID
		uint32_t m_attributeIndex = 0; //!< Attribute index
		std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffer;
		std::shared_ptr<IndexBuffer> m_indexBuffer;
	};
}