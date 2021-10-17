/* \file OpenGLShader.h*/
#pragma once


#include "rendering/shaders.h"

namespace Engine
{
	/** \class OpenGLShader
	* \brief Shaders for OpenGL abstract
	*/
	class OpenGLShader: public Shader
	{
	public:
		OpenGLShader(const char* vertexFilepath, const char* fragmentFilepath);
		OpenGLShader(const char* filepath);
		virtual ~OpenGLShader();
		virtual uint32_t getID() const override{return m_OpenGL_ID;}

		virtual void uploadInt(const char* name, int value);
		virtual void uploadFloat(const char* name, float value);
		virtual void uploadFloat2(const char* name, const glm::vec2& value);
		virtual void uploadFloat3(const char* name, const glm::vec3& value);
		virtual void uploadFloat4(const char* name, const glm::vec4& value);
		virtual void uploadMat4(const char* name, const glm::mat4& value);
	private:
		uint32_t m_OpenGL_ID;
		void compileAndLink(const char* vertexShaderSrc, const char* fragmentShaderSrc);
	};
}