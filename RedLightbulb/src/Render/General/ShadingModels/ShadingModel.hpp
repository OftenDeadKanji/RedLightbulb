#pragma once
#include "../Material/Material.hpp"
#include "Render/General/Instance/Instance.hpp"

namespace RedLightbulb
{
	class Mesh;
	class SubMesh;
	class Camera;
	struct Material;

	class ShadingModel
	{
	public:

		struct PerMaterialsSet
		{
			std::vector<rPtr<Material>> materials;
			std::vector<uPtr<MeshInstance>> instances;
		};

		struct PerMesh
		{
			rPtr<Mesh> mesh;
			std::vector<PerMaterialsSet> perMaterialsSet;
		};

	public:
		virtual void create() = 0;
		virtual void destroy() = 0;

		void setDefaultMaterial(rPtr<Material> material);

		void render(const Camera& camera);

		virtual void addMesh(rPtr<Mesh>& mesh, std::vector<rPtr<Material>>& materials, const MeshInstance& instance);
	protected:
		virtual void createBuffer(PerMesh& perMesh) = 0;
		virtual sPtr<Material> castToAppropriateMaterial(sPtr<Material> material) = 0;

		virtual void bindShader() = 0;
		virtual void bindBuffers(PerMesh& perMesh) = 0;
		virtual void bindUniforms(Material& material) = 0;
		virtual void updateInstanceBuffer(const PerMaterialsSet& perMaterialSet) = 0;
		virtual void draw(const SubMesh& subMesh, const PerMaterialsSet& perMaterialSet) = 0;

		std::vector<PerMesh> m_meshes;
		rPtr<Material> m_defaultMaterial;

	};

	inline void ShadingModel::setDefaultMaterial(rPtr<Material> material)
	{
		m_defaultMaterial = material;
	}

	void ShadingModel::render(const Camera& camera)
	{
		bindShader();

		for (PerMesh& perMesh : m_meshes)
		{
			bindBuffers(perMesh);

			const std::vector<SubMesh>& subMeshes = perMesh.mesh->getSubMeshes();

			int subMeshesCount = subMeshes.size();
			for (int subMeshIndex = 0; subMeshIndex < subMeshesCount; subMeshIndex++)
			{
				const SubMesh& subMesh = subMeshes[subMeshIndex];

				for (const PerMaterialsSet& perMaterialSet : perMesh.perMaterialsSet)
				{
					const rPtr<Material> material = perMaterialSet.materials[subMeshIndex];
					bindUniforms(*material);

					updateInstanceBuffer(perMaterialSet);

					draw(subMesh, perMaterialSet);
				}
			}
		}
	}

	inline void ShadingModel::addMesh(rPtr<Mesh>& mesh, std::vector<rPtr<Material>>& materials, const MeshInstance& instance)
	{
		int materialsCount = mesh->getMaterials().size();
		int inMaterialsCount = materials.size();

		if (inMaterialsCount > materialsCount)
		{
			return;
		}

		if (inMaterialsCount < materialsCount)
		{
			materials.resize(materialsCount);
		}

		for (int i = 0; i < materialsCount; i++)
		{
			if (materials[i] == nullptr)
			{
				materials[i] = m_defaultMaterial;
			}
		}

		uPtr<MeshInstance> newInstance = std::make_unique<MeshInstance>(instance);

		// do we already have this mesh?
		for (PerMesh& perMesh : m_meshes)
		{
			if (perMesh.mesh == mesh) // yes
			{
				for (PerMaterialsSet& perMaterialSet : perMesh.perMaterialsSet)
				{
					for (int i = 0; i < materialsCount; i++)
					{
						if (materials[i] == perMaterialSet.materials[i])
						{
							// we've found the same materials set - we can just add a new instance element
							perMaterialSet.instances.push_back(std::move(newInstance));

							return;
						}
					}
				}

				// we need to add a new materials set
				PerMaterialsSet newPerMaterialsSet;
				newPerMaterialsSet.materials = materials;
				newPerMaterialsSet.instances.push_back(std::move(newInstance));

				perMesh.perMaterialsSet.push_back(newPerMaterialsSet);

				return;
			}
		}

		// we add completely new mesh

		PerMaterialsSet perMaterialSet;
		perMaterialSet.materials = materials;
		perMaterialSet.instances.push_back(std::move(newInstance));

		PerMesh perMeshToAdd;
		perMeshToAdd.mesh = mesh;
		perMeshToAdd.perMaterialsSet.push_back(perMaterialSet);

		m_meshes.push_back(perMeshToAdd);
		createBuffer(m_meshes.back());
	}
}
