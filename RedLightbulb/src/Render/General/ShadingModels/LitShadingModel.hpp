#ifndef __LIT_SHADEING_MODEL_HPP__
#define __LIT_SHADEING_MODEL_HPP__
#include "ShadingModel.hpp"
#include "../Material/MaterialLit.hpp"

namespace RedLightbulb
{
	struct InstanceLit
	{
		Math::Mat4f transform;
	};

	class LitShadingModel
		: public ShadingModel<MaterialLit, InstanceLit>
	{
	public:
		virtual void create() override;
		virtual void destroy() override;

	private:
		virtual sPtr<MaterialLit> castToAppropriateMaterial(sPtr<Material> material) override;
	};
}

#endif
