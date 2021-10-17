/** \file Render3D.cpp */

#include "engine_pch.h"
#include <glad/glad.h>
#include "Rendering/Render3D.h"

namespace Engine
{
	std::shared_ptr<Render3D::InternalData> Render3D::s_data = nullptr;

	void Render3D::init()
	{
		s_data.reset(new InternalData);

		unsigned char whitePx[4] = { 255, 255, 255, 255 };
		std::shared_ptr<Texture>plainWhiteTex;
		s_data->defaultTexture.reset(Texture::create2(1, 1, 4, whitePx));
		s_data->defaultTint = { 1.f,1.f,1.f,1.f };
	}
	void Render3D::begin(const SceneWideUniforms& sceneWideUniforms)
	{
		s_data->sceneWideUniforms = sceneWideUniforms;
	}

	void Render3D::submit(const std::shared_ptr<VertexArray>& geometry, const std::shared_ptr<Material>& material, const glm::mat4& model)
	{
		// Bind shader
		glUseProgram(material->getShader()->getID());
		//Apply sceneWideUniforms
		for (auto& dataPair : s_data->sceneWideUniforms)
		{
			const char* nameOfUniform = dataPair.first;
			ShaderDataType& sdt = dataPair.second.first;
			void* addressOfValue = dataPair.second.second;

			switch (sdt)
			{
			case ShaderDataType::Int:
				material->getShader()->uploadInt(nameOfUniform, *(int*)addressOfValue);
				break;
			case ShaderDataType::Float3:
				material->getShader()->uploadFloat3(nameOfUniform, *(glm::vec3*)addressOfValue);
				break;
			case ShaderDataType::Float4:
				material->getShader()->uploadFloat4(nameOfUniform, *(glm::vec4*)addressOfValue);
				break;
			case ShaderDataType::Mat4:
				material->getShader()->uploadMat4(nameOfUniform, *(glm::mat4*)addressOfValue);
				break;
			}
		}
		
		//Apply material uniforms (per draw uniforms)
		material->getShader()->uploadMat4("u_model", model);

		if (material->isFlagSet(Material::flag_texture)) glBindTexture(GL_TEXTURE_2D, material->getTexture()->getID());
		else glBindTexture(GL_TEXTURE_2D, s_data->defaultTexture->getID());
		material->getShader()->uploadInt("u_texData", 0);

		if (material->isFlagSet(Material::flag_tint)) material->getShader()->uploadFloat4("u_tint", material->getTint());
		else material->getShader()->uploadFloat4("u_tint", s_data->defaultTint);

		//Bind the geometry (VAOs and IBOs)
		glBindVertexArray(geometry->getRenderID());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->getIndexBuffer()->getRenderID());

		glDrawElements(GL_TRIANGLES, geometry->getDrawCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Render3D::end()
	{
		s_data->sceneWideUniforms.clear();
	}
}