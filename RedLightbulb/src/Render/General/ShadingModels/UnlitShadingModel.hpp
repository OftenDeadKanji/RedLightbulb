#pragma once
#include "ShadingModel.hpp"
#include "../Material/MaterialUnlit.hpp"

namespace RedLightbulb
{
	struct InstanceUnlit
	{
		Math::Mat4f transform;
	};

	class UnlitShadingModel
		: public ShadingModel<MaterialUnlit, InstanceUnlit>
	{
	public:
		virtual void create() override;
		virtual void destroy() override;

	private:
		virtual sPtr<MaterialUnlit> castToAppropriateMaterial(sPtr<Material> material) override;
	};
}
