#pragma once
#include "../../General/Texture/Texture.hpp"

namespace RedLightbulb
{
	class ShaderOpenGL;

	class TextureOpenGL : public Texture
	{
	public:
		explicit TextureOpenGL(TextureType type);
		~TextureOpenGL();

		void create(const void* data, int width, int height);
		void destroy();

		void bind();
		void unbind();

		void setToSlot(int slot, const std::string& name) const override;

	private:
		GLuint m_id = 0;
		GLenum m_glType;
	};
}
