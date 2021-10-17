/** \file Render3D.h */
#pragma once

#include <glm/glm.hpp>
#include <rendering/RendererCommon.h>
#include "rendering/renderAPI.h"

namespace Engine
{

	using SceneWideUniforms = std::unordered_map<const char*, std::pair<ShaderDataType, void*>>;
	/** \class Material
	** \brief holds the data about the material for the model. 
	*/
	class Material
	{
	public:
		Material(const std::shared_ptr<Shader>& shader) :
			m_shader(shader), m_flags(0), m_texture(nullptr), m_tint(glm::vec4(0.f))
		{}
		Material(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& texture, const glm::vec4& tint) :
			m_shader(shader), m_texture(texture), m_tint(tint)
		{
			setFlag(flag_texture | flag_tint);
		}
		Material(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& texture) :
			m_shader(shader), m_texture(texture), m_tint(glm::vec4(0.f))
		{
			setFlag(flag_texture);
		}
		Material(const std::shared_ptr<Shader>& shader, const glm::vec4& tint) :
			m_shader(shader), m_texture(nullptr), m_tint(tint)
		{
			setFlag(flag_tint);
		}

		constexpr static uint32_t flag_texture = 1 << 0;
		constexpr static uint32_t flag_tint = 1 << 1;

		inline std::shared_ptr<Shader> getShader() const { return m_shader; }
		inline std::shared_ptr<Texture> getTexture() const { return m_texture; }
		inline glm::vec4 getTint() const { return m_tint; }
		bool isFlagSet(uint32_t flag) const { return m_flags & flag; }

		void setTexture(const std::shared_ptr<Texture>& texture) { m_texture = texture; }
		void setTint(const glm::vec4& tint) { m_tint = tint; }

	private:
		uint32_t m_flags = 0;
		std::shared_ptr<Shader>m_shader;
		std::shared_ptr<Texture>m_texture;
		glm::vec4 m_tint;
		void setFlag(uint32_t flag) { m_flags = m_flags | flag; }

	};
	/** \class Render3D
	** \brief Class which allows you to render 3D geometry instantly
	*/
	class Render3D
	{
	public:
		static void init();
		static void begin(const SceneWideUniforms& sceneWideUniforms);
		static void submit(const std::shared_ptr<VertexArray>& geometry, const std::shared_ptr<Material>& material, const glm::mat4& model);;
		static void end();

	private:
		struct InternalData
		{
			SceneWideUniforms sceneWideUniforms;
			std::shared_ptr<Texture> defaultTexture;
			glm::vec4 defaultTint;
		};

		static std::shared_ptr<InternalData> s_data;

	};
}