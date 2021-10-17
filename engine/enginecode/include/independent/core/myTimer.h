/**\file timer.h */

#pragma once

#include <chrono>

namespace Engine
{
	/**
\class Timer 
** \brief interface class for the timers
*/
	class Timer
	{
	public:
		virtual void start() = 0; //!< Start the timer
		virtual void reset() = 0; //!< Reset the timer
		virtual float getElapsedTime() = 0; //!< Get the time elapsed since the last start or restart

	};

	/**
	\class ChronoTimer
	** \brief chrono timer class
	*/
	class ChronoTimer : public Timer
	{
	public:
		virtual inline void start() { m_startPoint = std::chrono::high_resolution_clock::now(); }
		virtual inline void reset() { m_startPoint = std::chrono::high_resolution_clock::now(); }
		virtual float getElapsedTime()
		{
			m_endPoint = std::chrono::high_resolution_clock::now();
			std::chrono::duration<float, std::milli> elapsed = m_endPoint - m_startPoint;
			return elapsed.count() / 1000.f;
		}
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_startPoint;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_endPoint;
	};
}