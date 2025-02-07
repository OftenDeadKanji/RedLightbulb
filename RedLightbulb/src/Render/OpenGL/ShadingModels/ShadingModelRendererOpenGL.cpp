#include "pch.h"
#include "ShadingModelRendererOpenGL.hpp"

#include "Render/OpenGL/Objetcs/VAO.hpp"

namespace RedLightbulb
{
	//void ShadingModelRendererOpenGL::create(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
	//{
	//	m_shader.create(vertexShaderFile, fragmentShaderFile);
	//}
	void ShadingModelRendererOpenGL::bindShader()
	{
		m_shader.bind();
	}

	void ShadingModelRendererOpenGL::bindBuffers(sPtr<Mesh> mesh)
	{
		for(auto& buffer : m_buffers)
		{
			if(buffer.first == mesh)
			{
				buffer.second.bind();
			}
		}
	}

	void ShadingModelRendererOpenGL::bindMaterials()
	{

	}

	void ShadingModelRendererOpenGL::updateInstanceBuffer()
	{
	}

	void ShadingModelRendererOpenGL::draw()
	{
	}
}
