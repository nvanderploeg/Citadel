#include "timer.h"

namespace citadel
{
	void Timer::Tick(const Time& deltaTime)
	{
		if (!m_isActive)
			return;

		m_progress += deltaTime;
		while (m_progress >= m_duration)
		{
			m_progress -= m_duration;
			m_lambda();
		}
	}

	Timer& Timer::Every(f32 frequency, std::function<void(void)> lambda)
	{
		m_duration = Time::seconds(frequency);
		m_lambda = std::move(lambda);
		return *this;
	}
}