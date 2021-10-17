/** \file Render2D.cpp */
#include "engine_pch.h"

#include"glad/glad.h"
#include "rendering/Render2D.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{
	std::shared_ptr<Render2D::InternalData> Render2D::s_data;


	void Render2D::init()
	{
		s_data.reset(new InternalData);

		unsigned char whitePx[4] = { 255, 255, 255, 255 };
		std::shared_ptr<Texture>plainWhiteTex;
		s_data->defaultTexture.reset(Texture::create2(1, 1, 4, whitePx));

		s_data->defaultTint = { 1.f,1.f,1.f,1.f };

		s_data->model = glm::mat4(1.f);

		s_data->shader.reset(Shader::create("./assets/shaders/quad1.glsl"));

		float vertices[4 * 4] = {
		-0.5f,-0.5f,0.f,0.f,
		-0.5f,0.5f,0.f,1.f,
		0.5f,0.5f,1.f,1.f,
		0.5f,-0.5f,1.f,0.f,
		};

		uint32_t indices[4] = { 0,1,2,3 };
		std::shared_ptr<IndexBuffer>IBO;
		std::shared_ptr<VertexBuffer>VBO;

		s_data->VAO.reset(VertexArray::create());
		VBO.reset(VertexBuffer::create(vertices, sizeof(vertices), BufferLayout({ ShaderDataType::Float2, ShaderDataType::Float2 })));
		IBO.reset(IndexBuffer::create(indices, 4));
		s_data->VAO->addVertexBuffer(VBO);
		s_data->VAO->setIndexBuffer(IBO);
	}

	void Render2D::begin(const SceneWideUniforms& swu)
	{
		glUseProgram(s_data->shader->getID());

		for (auto& dataPair : swu)
		{
			const char* nameOfUniform = dataPair.first;
			ShaderDataType sdt = dataPair.second.first;
			void* addressOfValue = dataPair.second.second;

			switch (sdt)
			{
			case ShaderDataType::Int:
				s_data->shader->uploadInt(nameOfUniform, *(int*)addressOfValue);
				break;
			case ShaderDataType::Float3:
				s_data->shader->uploadFloat3(nameOfUniform, *(glm::vec3*)addressOfValue);
				break;
			case ShaderDataType::Float4:
				s_data->shader->uploadFloat4(nameOfUniform, *(glm::vec4*)addressOfValue);
				break;
			case ShaderDataType::Mat4:
				s_data->shader->uploadMat4(nameOfUniform, *(glm::mat4*)addressOfValue);
				break;
			}
		}
		

		glBindVertexArray(s_data->VAO->getRenderID());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_data->VAO->getIndexBuffer()->getRenderID());
	}

	void Render2D::submit(const Quad& quad, const glm::vec4& tint)
	{
		Render2D::submit(quad, tint, s_data->defaultTexture);

	}

	void Render2D::submit(const Quad& quad, const std::shared_ptr<Texture>& texture)
	{
		Render2D::submit(quad, s_data->defaultTint, texture);
	}

	void Render2D::submit(const Quad& quad, const glm::vec4& tint, const std::shared_ptr<Texture>& texture)
	{
		glBindTexture(GL_TEXTURE_2D, texture->getID());
		s_data->model = glm::scale(glm::translate(glm::mat4(1.f), quad.m_translate), quad.m_scale);

		s_data->shader->uploadInt("u_texData", 0);
		s_data->shader->uploadFloat4("u_tint", tint);
		s_data->shader->uploadMat4("u_model", s_data->model);


		glBindVertexArray(s_data->VAO->getRenderID());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_data->VAO->getIndexBuffer()->getRenderID());

		glDrawElements(GL_QUADS, s_data->VAO->getDrawCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Render2D::submit(const Quad& quad, const glm::vec4& tint, const std::shared_ptr<Texture>& texture, float angle, bool degrees)
	{
		if (degrees) angle = glm::radians(angle);

		glBindTexture(GL_TEXTURE_2D, texture->getID());
		s_data->model = glm::scale(glm::rotate(glm::translate(glm::mat4(1.f), quad.m_translate), angle, { 0.f,0.f,1.f }), quad.m_scale);

		s_data->shader->uploadInt("u_texData", 0);
		s_data->shader->uploadFloat4("u_tint", tint);
		s_data->shader->uploadMat4("u_model", s_data->model);


		glBindVertexArray(s_data->VAO->getRenderID());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_data->VAO->getIndexBuffer()->getRenderID());
		glDrawElements(GL_QUADS, s_data->VAO->getDrawCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Render2D::submit(const Quad& quad, const std::shared_ptr<Texture>& texture, float angle, bool degrees)
	{
		Render2D::submit(quad, s_data->defaultTint, texture, angle, degrees);
	}

	void Render2D::submit(const Quad& quad, const glm::vec4& tint, float angle, bool degrees)
	{
		Render2D::submit(quad, tint, s_data->defaultTexture, angle, degrees);
	}

	Quad Quad::createCentreHalfExtrents(const glm::vec2& centre, const glm::vec2& halfExtents)
	{
		Quad result;

		result.m_translate = glm::vec3(centre, 0.f);
		result.m_scale = glm::vec3(halfExtents * 2.f, 1.f);

		return result;
	}

	void Render2D::end()
	{
	}
}