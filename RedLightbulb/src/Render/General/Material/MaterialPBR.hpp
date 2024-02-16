#ifndef __MATERIAL_PBR_HPP__
#define __MATERIAL_PBR_HPP__
#include "Material.hpp"
#include "../Texture/Texture.hpp"

namespace RedLightbulb
{
	struct MaterialUnlit;

	struct MaterialPBR
		: public Material
	{
		Math::Vec3f baseColor = Math::Vec3f(1.0f, 1.0f, 1.0f);
		std::shared_ptr<Texture> baseColorTexture;

		std::shared_ptr<Texture> normalTexture;

		float roughness = 1.0f;
		bool usesRoughnessTexture = false;

		float metallic = 0.0f;
		bool usesMetallicTexture = false;

		std::shared_ptr<Texture> ARMTexture;

		virtual MaterialUnlit toUnlit() override;
		virtual MaterialLit toLit() override;
	};
}

#endif