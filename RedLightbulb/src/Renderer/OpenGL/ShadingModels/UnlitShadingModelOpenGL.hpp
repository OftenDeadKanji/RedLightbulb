#pragma once
#include "../../General/ShadingModels/UnlitShadingModel.hpp"
#include "../Shader/ShaderOpenGL.hpp"
#include "../Objetcs/VAO.hpp"

namespace RedLightbulb
{
	class UnlitShadingModelOpenGL
		: public UnlitShadingModel
	{
	public:
		UnlitShadingModelOpenGL();

		virtual void create() override;
		virtual void destroy() override;

		virtual void render() override;
	private:
		virtual void createBuffer(PerMesh& perMesh) override;

		bool m_isInitialized = false;

		ShaderOpenGL m_shader;
		std::vector<std::pair<PerMesh*, VAO>> m_buffers;
	};
}
