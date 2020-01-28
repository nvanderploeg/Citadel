
#include "citadelSystem.h"

namespace citadel {

	Clock::Clock()
		: m_startTime(Time::getCurrentTime())
	{

	}

	Time Clock::getElapsedTime() const
	{
		return Time::getCurrentTime() - m_startTime;
	}

	Time Clock::restart()
	{
		Time now = Time::getCurrentTime();
		Time elapsed = now - m_startTime;
		m_startTime = now;
		return elapsed;
	}

} // namespace n0
