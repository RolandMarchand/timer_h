/*
 * Copyright (c) 2022 moowool195@gmail.com. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#pragma once

#include <chrono>

/*
 * USAGE
 *
 * Timer begins recording time as soon as it is instanced.
 *
 * get() returns the recorded time in milliseconds.
 *
 * pause() toggles the timer. When called once, it stops recording time,
 * when called twice, it records time back to where you left it.
 *
 * reset() resets the recorded time back to 0ms.
 */
class Timer
{
	using Us = std::chrono::microseconds;
	using Clock = std::chrono::high_resolution_clock;
	using TimeStamp = std::chrono::time_point<Clock>;

	const Us zero_paused_time {Us().zero()};
	const TimeStamp steady_min_time {TimeStamp::min()};

	TimeStamp m_StartTimePoint;
	TimeStamp m_StartPauseTimePoint;
	TimeStamp m_EndPauseTimePoint;

	Us pausedTime;
	bool paused;

	// Returns the epoch time of a std::chrono::time_point as a duration
	template<class Period>
	Period getEpoch(const TimeStamp& point) const{
		return std::chrono::time_point_cast<Period>(point).time_since_epoch();
	}

	/* Returns the recorded time. */
	template<class Duration>
	Duration getDuration() const{
		TimeStamp endTimePoint = TimeStamp(Clock::now());

		Duration start {getEpoch<Duration>(m_StartTimePoint)};
		Duration end {getEpoch<Duration>(endTimePoint)};
		
		Us tmpPausedTime {pausedTime};
		if (paused){
			Us pauseStart {getEpoch<Us>(m_StartPauseTimePoint)};
			Us pauseEnd {getEpoch<Us>(TimeStamp(Clock::now()))};
			
			tmpPausedTime += pauseEnd - pauseStart;
		}

		Duration duration = end - start - std::chrono::duration_cast<Duration>(tmpPausedTime);

		return duration;
	}

public:
	Timer()
	: m_StartTimePoint(Clock::now()),
	  m_StartPauseTimePoint(steady_min_time),
	  m_EndPauseTimePoint(steady_min_time),
	  pausedTime(zero_paused_time),
	  paused(false)
	{
	}

	/* Toggles the timer to record paused time. */
	/* It will be subtracted from the total recorded time. */
	void pause(){
		if (!paused){
			m_StartPauseTimePoint = std::chrono::time_point<Clock>(Clock::now());
			m_EndPauseTimePoint = steady_min_time;
		} else {
			m_EndPauseTimePoint = std::chrono::time_point<Clock>(Clock::now());

			Us start {getEpoch<Us>(m_StartPauseTimePoint)};
			Us end {getEpoch<Us>(m_EndPauseTimePoint)};

			pausedTime += end - start;
		}

		paused = !paused;
	}

	/* Resets current and paused time, and unpauses. */
	void reset(){
		m_StartTimePoint = Clock::now();

		m_StartPauseTimePoint = steady_min_time;
		m_EndPauseTimePoint = steady_min_time;

		pausedTime = zero_paused_time;

		paused = false;
	}

	/* std::chrono::duration, e.g. std::chrono::seconds*/
	template<class Duration>
	long long get(){
		return getDuration<Duration>().count();
	}
};
