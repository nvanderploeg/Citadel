#pragma once

#include "tickable.h"
#include "system/clock.h"

namespace citadel
{

	class Timer : public Clock, public ITickable
	{
	protected:
		Time m_duration;
		Time m_progress;
		std::function<void(void)> m_lambda;

	public:
		virtual void Tick(const Time& deltaTime) override;

		Timer& Every(f32 frequency, std::function<void(void)> lamda);
	};

} // namespace Timer