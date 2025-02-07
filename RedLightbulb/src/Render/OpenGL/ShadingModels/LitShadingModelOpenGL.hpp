#ifndef __LIT_SHADING_MODEL_OPENGL_HPP__
#define __LIT_SHADING_MODEL_OPENGL_HPP__

#include "../../General/ShadingModels/LitShadingModel.hpp"
#include "Render/OpenGL/Shader/ShaderOpenGL.hpp"
#include "Render/OpenGL/Objetcs/VAO.hpp"
#include "Render/OpenGL/Objetcs/UBO.hpp"

namespace RedLightbulb
{
	class LitShadingModelOpenGL
		: public LitShadingModel
	{
	public:
		LitShadingModelOpenGL();

		virtual void create() override;
		virtual void destroy() override;

	private:
		virtual void createBuffer(PerMesh& perMesh) override;

	protected:
		void bindShader() override;
		void bindBuffers(PerMesh& perMesh) override;
		void bindUniforms(sPtr<MaterialLit> material) override;
		void updateInstanceBuffer(PerMaterialsSet& perMaterialSet) override;
		void draw(const SubMesh& subMesh, PerMaterialsSet& perMaterialSet) override;

	private:
		bool m_isInitialized = false;

		ShaderOpenGL m_shader;
		std::vector<std::pair<PerMesh*, VAO>> m_buffers;
		VAO* m_boundVAO;

		struct MaterialUniform
		{
			Math::Vec3f baseColor;
			int usesBaseColorTexture;

			float roughness;
			int usesRoughnessTexture;

			float metallic;
			int usesMetallicTexture;

			int usesNormalTexture;
		};
		UniformBufferObject m_materialUBO;
	};
}
#endif
