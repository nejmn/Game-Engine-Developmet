/** \file RendererCommon.h */

#pragma once
#include <glm/glm.hpp>
#include <unordered_map>
#include <memory>
#include "rendering/shaderDataType.h"
#include "rendering/VertexArray.h"
#include "rendering/Textures.h"
#include "rendering/shaders.h"

namespace Engine
{
	using SceneWideUniforms = std::unordered_map<const char*, std::pair<ShaderDataType, void*>>;
}