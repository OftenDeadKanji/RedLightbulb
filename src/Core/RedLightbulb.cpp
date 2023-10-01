#include "RedLightbulb.hpp"

namespace RedLightbulb
{

	RedLighbulb::~RedLighbulb()
	{
		deinit();
	}

	Window& RedLighbulb::getWindow()
	{
		return m_mainWindow;
	}

	void RedLighbulb::init()
	{
		if (m_isInitialised)
		{
			//deinit?
		}
		else
		{
			m_mainWindow.create();
		}
	}

	void RedLighbulb::deinit()
	{
		if (m_isInitialised)
		{
			m_mainWindow.destroy();
		}
	}
}
