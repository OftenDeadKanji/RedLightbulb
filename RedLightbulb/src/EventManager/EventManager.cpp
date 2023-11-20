#include "EventManager.hpp"
#include "../Config/OSInfo.hpp"
#include "../Window/Window.hpp"

namespace RedLightbulb
{
	std::optional<Event> EventManager::getNextEvent()
	{
		if (m_eventsQueue.empty())
		{
			return {};
		}

		Event nextEvent = std::move(m_eventsQueue.front());
		m_eventsQueue.pop();

		return nextEvent;
	}
}