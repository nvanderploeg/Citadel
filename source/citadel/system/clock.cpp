
#include "citadelSystem.h"

namespace citadel {

	Clock::Clock()
		: m_startTime(Time::getCurrentTime())
		, m_isActive(false)
	{

	}

	Time Clock::getElapsedTime() const
	{
		return m_isActive ? Time::getCurrentTime() - m_startTime : Time::microseconds(0);
	}

	Time Clock::restart()
	{
		Time now = Time::getCurrentTime();
		Time elapsed = now - m_startTime;
		m_startTime = now;
		return elapsed;
	}

	Time Clock::start()
	{
		m_isActive = true;
		m_startTime = Time::getCurrentTime();
		return m_startTime;
	}

	// TODO: should this return the current time when the clock stops, or the elapsed time?
	Time Clock::stop()
	{
		m_isActive = false;
		return Time::getCurrentTime();
	}

} // namespace n0
