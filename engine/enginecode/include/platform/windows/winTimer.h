/** \file winTimer */
#pragma once

#include <Windows.h>
#include "core/myTimer.h"

namespace Engine
{
	/** \class winTimer
	*	Windows specific timer which use queryPerformanceCount
	*/

	class WinTimer: public Timer
	{
		virtual void start() override 
		{
			QueryPerformanceFrequency(&m_frequency);
			QueryPerformanceCounter(&m_startTime);

		};
		virtual void reset() override { QueryPerformanceCounter(&m_startTime); };
		virtual float getElapsedTime() override
		{
			QueryPerformanceCounter(&m_endTime);
			float result = (m_endTime.QuadPart - m_startTime.QuadPart) * 1000.f / m_frequency.QuadPart;
			result /= 1000.f;
			return result;
		}
	private:
		LARGE_INTEGER m_startTime;	//!< Start time for the timer
		LARGE_INTEGER m_endTime;	//!< End time for the timer
		LARGE_INTEGER m_frequency;	//!< Tick per second of this CPU
	};

}