/** \file Render2D.h */

#pragma once

#include "rendering/RendererCommon.h"

namespace Engine
{

	class Quad
	{
	public:
		static Quad createCentreHalfExtrents(const glm::vec2& centre, const glm::vec2& halfExtents);
	
	private:
		glm::vec3 m_translate = glm::vec3(0.f);
		glm::vec3 m_scale = glm::vec3(1.f);
		friend class Render2D;
	};

	/** \class Render2D
	** \brief Class which allows you to render 2D objects in the game engine
	*/
	class Render2D
	{
	public:
		static void init(); //!<initialize the internal data of the renderer
		static void begin(const SceneWideUniforms& swu); //!< Creating 2D scene
		static void submit(const Quad& quad, const glm::vec4& tint); //!< Render a tinted quad

		static void submit(const Quad& quad, const std::shared_ptr<Texture>& texture); //!< Render a textured quad
		static void submit(const Quad& quad, const glm::vec4& tint, const std::shared_ptr<Texture>& texture); //!< render a textured and tinted quad

		static void submit(const Quad& quad, const glm::vec4& tint, const std::shared_ptr<Texture>& texture, float angle, bool degrees = false); //!< render a textured, rotated and tinted quad
		static void submit(const Quad& quad, const std::shared_ptr<Texture>& texture, float angle, bool degrees = false); //!< render a textured, rotated not tinted quad
		static void submit(const Quad& quad, const glm::vec4& tint, float angle, bool degrees = false); //!< render quad not textured, but tinted and rotated
		static void end();
	private:
		struct InternalData
		{
			std::shared_ptr<Texture> defaultTexture;
			glm::vec4 defaultTint;
			std::shared_ptr<Shader> shader;
			std::shared_ptr<VertexArray> VAO;
			glm::mat4 model;
		};

		static std::shared_ptr<InternalData> s_data;
	};
}