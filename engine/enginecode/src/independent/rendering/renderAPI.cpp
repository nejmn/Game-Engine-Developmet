/* \file renderAPI.cpp*/

#include "engine_pch.h"
#include "rendering/renderAPI.h"
#include "systems/loggin.h"

#include "rendering/indexBuffer.h"
#include "rendering/VertexArray.h"
#include "rendering/VertexBuffer.h"
#include "rendering/Textures.h"
#include "rendering/shaders.h"

#include "platform/OpenGL/OpenGLIndexBuffer.h"
#include "platform/OpenGL/OpenGLVertexArray.h"
#include "platform/OpenGL/OpenGLVertexBuffer.h"
#include "platform/OpenGL/OpenGLTextures.h"
#include "platform/OpenGL/OpenGLShader.h"

namespace Engine
{
	RenderAPI::API RenderAPI::s_API = RenderAPI::API::OpenGL;

	IndexBuffer* IndexBuffer::create(uint32_t* indices, uint32_t count)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None :
			Log::error("Not having a rendering API is not currently supported");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indices, count);
			break;
		case RenderAPI::API::Direct3D:
			Log::error("Direct3D is not currently supported");
			break;
		case RenderAPI::API::Vulkan:
			Log::error("Vulkan is not currently supported");
			break;
		}
	}

	VertexBuffer* VertexBuffer::create(void* vertices, uint32_t size, BufferLayout layout)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			Log::error("Not having a rendering API is not currently supported");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLVertexBuffer(vertices, size, layout);
			break;
		case RenderAPI::API::Direct3D:
			Log::error("Direct3D is not currently supported");
			break;
		case RenderAPI::API::Vulkan:
			Log::error("Vulkan is not currently supported");
			break;
		}
	}

	VertexArray* VertexArray::create()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			Log::error("Not having a rendering API is not currently supported");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLVertexArray();
		case RenderAPI::API::Direct3D:
			Log::error("Direct3D is not currently supported");
			break;
		case RenderAPI::API::Vulkan:
			Log::error("Vulkan  is not curently suppoerted");
			break;
		}
	}

	Texture* Texture::create(const char* filepath)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			Log::error("Not having a rendering API is not currently supported");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLTextures(filepath);
		case RenderAPI::API::Direct3D:
			Log::error("Direct3D is not currently supported");
			break;
		case RenderAPI::API::Vulkan:
			Log::error("Vulkan  is not curently suppoerted");
			break;
		}

	}

	Texture* Texture::create2(uint32_t width, uint32_t height, uint32_t channels, unsigned char* data)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			Log::error("Not having a rendering API is not currently supported");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLTextures(width, height, channels, data);
		case RenderAPI::API::Direct3D:
			Log::error("Direct3D is not currently supported");
			break;
		case RenderAPI::API::Vulkan:
			Log::error("Vulkan  is not curently suppoerted");
			break;
		}

	}

	Shader* Shader::create(const char* filepath)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			Log::error("Not having a rendering API is not currently supported");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLShader(filepath);
		case RenderAPI::API::Direct3D:
			Log::error("Direct3D is not currently supported");
			break;
		case RenderAPI::API::Vulkan:
			Log::error("Vulkan  is not curently suppoerted");
			break;
		}

	}
}

