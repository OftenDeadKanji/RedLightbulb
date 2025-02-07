#include "pch.h"
#include "LitShadingModelOpenGL.hpp"
#include "../Texture/TextureOpenGL.hpp"

namespace RedLightbulb
{
	LitShadingModelOpenGL::LitShadingModelOpenGL()
		: m_shader("Lit")
	{}
	void LitShadingModelOpenGL::create()
	{
		if (m_isInitialized)
		{
			// ???
		}

		m_shader.create("Shaders/Lit/LitVS.glsl", "Shaders/Lit/LitFS.glsl");
		m_materialUBO.create();

		m_isInitialized = true;
	}
	void LitShadingModelOpenGL::destroy()
	{
		if (m_isInitialized)
		{
			m_isInitialized = false;
		}
	}

	void LitShadingModelOpenGL::createBuffer(PerMesh& perMesh)
	{
		const auto& vertices = perMesh.mesh->getVertices();
		const auto& indices = perMesh.mesh->getIndices();

		std::pair<PerMesh, VAO> meshBuffer;

		m_buffers.emplace_back();
		m_buffers.back().first = &perMesh;

		auto& buffer = m_buffers.back().second;
		buffer.create();
		buffer.createP3TX2NM3TG3BT3IndexedInstancedBuffer(vertices, indices);
	}
	void LitShadingModelOpenGL::bindShader()
	{
		m_shader.bind();
	}
	void LitShadingModelOpenGL::bindBuffers(PerMesh& perMesh)
	{
		for (auto& buffer : m_buffers)
		{
			if (buffer.first == &perMesh)
			{
				buffer.second.bind();
				m_boundVAO = &buffer.second;
				break;
			}
		}
	}

	void LitShadingModelOpenGL::bindUniforms(sPtr<MaterialLit> material)
	{
		MaterialUniform uniform;

		uniform.baseColor = material->baseColor;
		if (material->baseColorTexture)
		{
			uniform.usesBaseColorTexture = true;
			material->baseColorTexture->setToSlot(0, "baseColorTexture");
		}

		if (material->normalTexture != nullptr)
		{
			uniform.usesNormalTexture = true;
			material->normalTexture->setToSlot(1, "normalTexture");
		}

		uniform.roughness = material->roughness;
		uniform.usesRoughnessTexture = material->usesRoughnessTexture;

		uniform.metallic = material->metallic;
		uniform.usesMetallicTexture = material->usesMetallicTexture;

		if (material->ARMTexture != nullptr)
		{
			material->ARMTexture->setToSlot(2, "armTexture");
		}

		m_materialUBO.bind();
		m_materialUBO.bufferData(&uniform, sizeof(uniform));
		m_materialUBO.setToSlot(3);
	}
	void LitShadingModelOpenGL::updateInstanceBuffer(PerMaterialsSet& perMaterialSet)
	{
		m_boundVAO->updateInstanceBuffer(perMaterialSet.instances.data(), sizeof(InstanceT) * perMaterialSet.instances.size());
	}

	void LitShadingModelOpenGL::draw(const SubMesh& subMesh, PerMaterialsSet& perMaterialSet)
	{
		if(m_boundVAO->withIndicesAndInstances())
		{
			glDrawElementsInstanced(GL_TRIANGLES, subMesh.getIndicesCount(), GL_UNSIGNED_INT, (void*)(subMesh.getFirstIndexIndex() * sizeof(unsigned int)), perMaterialSet.instances.size());
		}
		else if (m_boundVAO->withIndices())
		{
			glDrawElements(GL_TRIANGLES, subMesh.getIndicesCount(), GL_UNSIGNED_INT, (void*)(subMesh.getFirstIndexIndex() * sizeof(unsigned int)));
		}
	}
}
