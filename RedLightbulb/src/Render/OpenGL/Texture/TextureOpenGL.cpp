#include "pch.h"
#include "TextureOpenGL.hpp"
#include "../Shader/ShaderOpenGL.hpp"
#include "Render/OpenGL/RendererOpenGL.hpp"

namespace RedLightbulb
{
	TextureOpenGL::TextureOpenGL(TextureType type)
		: Texture(type)
	{
		switch (type)
		{
		case TextureType::Single2D:
			m_glType = GL_TEXTURE_2D;
			break;
		}
	}

	TextureOpenGL::~TextureOpenGL()
	{
		destroy();
	}

	void TextureOpenGL::create(const void* data, int width, int height)
	{
		if (m_id != 0)
		{
			// ?
		}

		glGenTextures(1, &m_id);
		bind();

		glTexParameteri(m_glType, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(m_glType, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(m_glType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(m_glType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(m_glType, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}

	void TextureOpenGL::destroy()
	{
		if (m_id != 0)
		{
			glDeleteTextures(1, &m_id);
			m_id = 0;
		}
	}
	void TextureOpenGL::bind()
	{
		glBindTexture(m_glType, m_id);
	}
	void TextureOpenGL::unbind()
	{
		glBindTexture(m_glType, 0);
	}
	void TextureOpenGL::setToSlot(int slot, const std::string& name) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(m_glType, m_id);

		auto* shader = sCast(RendererOpenGL&, RendererOpenGL::getInstance()).GetBoundShader();

		shader->setInt(slot, name);
	}
}
