#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__
#include "TextureType.hpp"

namespace RedLightbulb
{
	class Texture
	{
	public:
		explicit Texture(TextureType type);

		virtual void setToSlot(int slot, const std::string& name) const = 0;

	protected:
		TextureType m_type;
	};
}

#endif