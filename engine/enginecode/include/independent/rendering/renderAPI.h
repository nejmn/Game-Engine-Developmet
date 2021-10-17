/* \file renderAPI.h*/
#pragma once

namespace Engine
{
	/** \class RenderAPI 
	** \brief Choose which API we are using
	*/
	class RenderAPI
	{
	public:
		enum class API {None = 0, OpenGL =1, Direct3D=2, Vulkan=3};
		inline static API getAPI() { return s_API; }
	private:
		static API s_API; //!< Chosen API at the moment

	};
}