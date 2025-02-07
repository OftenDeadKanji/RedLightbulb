#pragma once

#include "../../General/ShadingModels/ShadingModelRenderer.hpp"
#include "Render/General/ShadingModels/ShadingModel.hpp"
#include "Render/OpenGL/Shader/ShaderOpenGL.hpp"

namespace RedLightbulb
{
	class VAO;

	class ShadingModelRendererOpenGL : public ShadingModelRenderer<ShaderOpenGL>
    {
    public:
    	//void create(const std::string& vertexShaderFile, const std::string& fragmentShaderFile) override;

	    void bindShader() override;
	    void bindBuffers(sPtr<Mesh> mesh) override;
	    void bindMaterials() override;
	    void updateInstanceBuffer() override;
	    void draw() override;

    protected:
		std::vector<std::pair<sPtr<Mesh>, VAO>> m_buffers;

    };
}
