#include "pch.h"
#include "RendererOpenGL.hpp"
#include "../../Config/OSInfo.hpp"

#include "../../Dependencies/glad/glad/wgl.h"
#include "../../Dependencies/glad/glad/gl.h"

#include "../../Window/WindowWindows.hpp"
#include "../General/Camera/Camera.hpp"

namespace RedLightbulb
{
	void RendererOpenGL::init()
	{
		createContext();
		initClearColors();

		m_unlitShadingModels = new UnlitShadingModelOpenGL();
		m_unlitShadingModels->create();

		m_litShadingModels = new LitShadingModelOpenGL();
		m_litShadingModels->create();

		m_perFrameUBO.create();

		glEnable(GL_DEPTH_TEST);
		glFrontFace(GL_CCW);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		
	}

	void RendererOpenGL::deinit()
	{
	#ifdef __OS_WINDOWS_64__
		WindowWindows* window = static_cast<WindowWindows*>(m_window);

		wglMakeCurrent(window->getHDC(), NULL);
		wglDeleteContext(m_context);
	#endif
	}

	void RendererOpenGL::render(float deltaTime, const Camera& camera)
	{
		clearBuffers();
		
		m_perFrameUBO.bind();
		Math::Mat4f arr[2] = { camera.getView(), camera.getProj() };
		m_perFrameUBO.bufferData((void*)(arr), 2 * sizeof(Math::Mat4f));
		m_perFrameUBO.setToSlot(1);
		
		m_unlitShadingModels->render(camera);
		m_litShadingModels->render(camera);
	}

	void RendererOpenGL::SetBoundShader(ShaderOpenGL* Shader)
	{
		CurrentlyBoundShader = Shader;
	}

	ShaderOpenGL* RendererOpenGL::GetBoundShader() const
	{
		return CurrentlyBoundShader;
	}

	void RendererOpenGL::createContext()
	{
	#ifdef __OS_WINDOWS_64__
		WindowWindows* window = static_cast<WindowWindows*>(m_window);

		PIXELFORMATDESCRIPTOR pixelFormatDesc =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA,
			32,
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			24,
			8,
			0,
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};

		int pixelFormatIndex = ChoosePixelFormat(window->getHDC(), &pixelFormatDesc);
		SetPixelFormat(window->getHDC(), pixelFormatIndex, &pixelFormatDesc);

		m_context = wglCreateContext(window->getHDC());
		wglMakeCurrent(window->getHDC(), m_context);

		gladLoaderLoadWGL(window->getHDC());

		const int pixelFormatAttribList[] =
		{
			WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
			WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
			WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
			WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
			WGL_COLOR_BITS_ARB, 32,
			WGL_DEPTH_BITS_ARB, 24,
			WGL_STENCIL_BITS_ARB, 8,
			0,
		};

		int pixelFormat;
		UINT numFormats;

		wglChoosePixelFormatARB(window->getHDC(), pixelFormatAttribList, NULL, 1, &pixelFormat, &numFormats);

		const int contextAttribList[] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
			WGL_CONTEXT_MINOR_VERSION_ARB, 6,
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			0,
		};

		HGLRC context = wglCreateContextAttribsARB(window->getHDC(), NULL, contextAttribList);

		wglMakeCurrent(window->getHDC(), NULL);
		wglDeleteContext(m_context);

		PIXELFORMATDESCRIPTOR pfd;
		DescribePixelFormat(window->getHDC(), pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
		SetPixelFormat(window->getHDC(), pixelFormat, &pfd);

		wglMakeCurrent(window->getHDC(), context);
		gladLoaderLoadGL();

		m_context = context;
	#endif
	}
	
	void RendererOpenGL::initClearColors()
	{
		m_clearColors.mainColorBuffer = Math::Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
	}
	
	void RendererOpenGL::clearBuffers()
	{
		glClearColor(m_clearColors.mainColorBuffer.x(), m_clearColors.mainColorBuffer.y(), m_clearColors.mainColorBuffer.z(), m_clearColors.mainColorBuffer.w());
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}