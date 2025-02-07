#pragma once

namespace RedLightbulb
{
	template<class ShaderType>
	class ShadingModelRenderer
	{
	public:
		virtual ~ShadingModelRenderer() = default;

		virtual void create(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);

		virtual void bindShader() = 0;
		virtual void bindBuffers(sPtr<Mesh> mesh) = 0;
		virtual void bindMaterials() = 0;
		virtual void updateInstanceBuffer() = 0;
		virtual void draw() = 0;
	protected:
		ShaderType m_shader;
	};

	template <class ShaderType>
	void ShadingModelRenderer<ShaderType>::create(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
	{
		m_shader.create(vertexShaderFile, fragmentShaderFile);
	}
}
