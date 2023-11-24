#pragma once
#include "../../General/Shader/Shader.hpp"


namespace RedLightbulb
{
	class ShaderOpenGL : public Shader
	{
	public:
		ShaderOpenGL() = default;
		explicit ShaderOpenGL(std::string name);

		void create(const std::string& vertexShaderFile, const std::string& fragmentShaderFile) override;
		void destroy() override;

		void setIntUniform(int value) override;
		void setFloatUniform(float value) override;
		void setVec2Uniform(const Vec2& value) override;
		void setVec2iUniform(const Vec2i& value) override;
		void setVec3Uniform(const Vec3& value) override;
		void setVec4Uniform(const Vec4& value) override;
		void setMat4Uniform(const Mat4& value) override;

		void bind() override;
	private:
		void loadVertexShaderFile(const std::string& vertexShaderFile);
		void loadFragmentShaderFile(const std::string& vertexShaderFile);

		GLuint m_id;
	};
}
