#ifndef __RENDERER_OPENGL_HPP__
#define __RENDERER_OPENGL_HPP__
#include "../General/Renderer.hpp"
#include "../../Config/OSInfo.hpp"

#include "../../Dependencies/OS/Windows.hpp"
#include "ShadingModels/UnlitShadingModelOpenGL.hpp"
#include "ShadingModels/LitShadingModelOpenGL.hpp"
#include "Objetcs/UBO.hpp"

namespace RedLightbulb
{
	class RendererOpenGL : public Renderer
	{
	public:
		void init() override;
		void deinit() override;

		void render(float deltaTime, const Camera& camera) override;

		void SetBoundShader(ShaderOpenGL* Shader);
		ShaderOpenGL* GetBoundShader() const;
	private:
		void createContext();
		void initClearColors();

		void clearBuffers();

		HGLRC m_context;

		ShaderOpenGL* CurrentlyBoundShader {};

		struct
		{
			Math::Vec4f mainColorBuffer;
		} m_clearColors;
		UniformBufferObject m_perFrameUBO;
	};
}
#endif