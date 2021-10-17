/* \file Shaders.h*/

#pragma once

#include <cstdint>
#include <glm/glm.hpp>
namespace Engine
{
	/**
	**\class Shader 
	** \brief abstraction of the shaders for the OpenGL
	*/
	class Shader
	{
	public:
		virtual ~Shader() = default;
		virtual inline uint32_t getID() const = 0;
		virtual void uploadInt(const char* name, int value) = 0;
		virtual void uploadFloat(const char* name, float value) = 0;
		virtual void uploadFloat2(const char* name, const glm::vec2& value) = 0;
		virtual void uploadFloat3(const char* name, const glm::vec3& value) = 0;
		virtual void uploadFloat4(const char* name, const glm::vec4& value) = 0;
		virtual void uploadMat4(const char* name, const glm::mat4& value) = 0;

		static Shader* create(const char* filepath);
		//static Shader* createChannels(const char* vertexFilepath, const char* fragmentFilepath);
	};
}