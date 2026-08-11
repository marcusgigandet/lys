/*
 * Copyright 2026 Marcus Gigandet
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

module lys:timer.impl;

import :timer;
import std;

namespace lys
{
	void Timer::start()
	{
		m_startTime = std::chrono::high_resolution_clock::now();
		m_prevTime	= m_startTime;
	}

	double Timer::delta()
	{
		const auto	 now{std::chrono::high_resolution_clock::now()};
		const double time{
			std::chrono::duration_cast<std::chrono::duration<double>>(now - m_prevTime).count()};
		m_prevTime = now;

		return time;
	}

	double Timer::peekDelta() const
	{
		const auto now{std::chrono::high_resolution_clock::now()};
		return std::chrono::duration_cast<std::chrono::duration<double>>(now - m_prevTime).count();
	}

	double Timer::elapsed()
	{
		const auto	 now{std::chrono::high_resolution_clock::now()};
		const double time{
			std::chrono::duration_cast<std::chrono::duration<double>>(now - m_startTime).count()};
		m_startTime = now;
		return time;
	}

	double Timer::peekElapsed() const
	{
		const auto now{std::chrono::high_resolution_clock::now()};
		return std::chrono::duration_cast<std::chrono::duration<double>>(now - m_startTime).count();
	}
} // namespace lys
