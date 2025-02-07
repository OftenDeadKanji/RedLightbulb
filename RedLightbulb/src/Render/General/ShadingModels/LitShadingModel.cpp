#include "pch.h"
#include "LitShadingModel.hpp"

namespace RedLightbulb
{
	void LitShadingModel::create()
	{}

	void LitShadingModel::destroy()
	{}

	sPtr<MaterialLit> LitShadingModel::castToAppropriateMaterial(sPtr<Material> material)
	{
		return std::make_shared<MaterialLit>(material->toLit());
	}
}
