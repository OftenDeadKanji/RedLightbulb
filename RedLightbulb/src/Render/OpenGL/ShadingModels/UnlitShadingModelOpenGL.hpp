#pragma once
#include "../../General/ShadingModels/UnlitShadingModel.hpp"
#include "../Shader/ShaderOpenGL.hpp"
#include "../Objetcs/VAO.hpp"
#include "../Objetcs/UBO.hpp"

namespace RedLightbulb
{
	class UnlitShadingModelOpenGL
		: public UnlitShadingModel
	{
	public:
		UnlitShadingModelOpenGL();

		virtual void create() override;
		virtual void destroy() override;

		virtual void render(const Camera& camera) override;
	private:
		virtual void createBuffer(PerMesh& perMesh) override;

		bool m_isInitialized = false;

		//ShaderOpenGL m_shader;

		struct MaterialUniform
		{
			Math::Vec3f baseColor;
			int usesBaseColorTexture;
		};
		UniformBufferObject m_materialUBO;
	};
}
