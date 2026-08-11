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

export module lys:timer;

import std;

namespace lys
{
	/**
	 * @brief A high-resolution timer for measuring time intervals.
	 */
	export class Timer
	{
		std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_prevTime;

	public:
		/**
		 * @brief Resets the timer to the current time.
		 */
		void start();

		/**
		 * @brief Gets the time elapsed since the last call to `delta()`.
		 *
		 * @return The time (in seconds) since the last call to `delta()`.
		 */
		[[nodiscard]] double delta();

		/**
		 * @brief Gets the time since the last `delta()` call without updating the timer.
		 *
		 * @return The time (in seconds) since the last `delta()` call.
		 */
		[[nodiscard]] double peekDelta() const;

		/**
		 * @brief Gets the total time elapsed since the timer was started or reset.
		 *
		 * @return The total time (in seconds) since the timer was started.
		 */
		[[nodiscard]] double elapsed();

		/**
		 * @brief Gets the total time elapsed since the timer was started, without updating the
		 * timer.
		 *
		 * @return The total time (in seconds) since the timer was started.
		 */
		[[nodiscard]] double peekElapsed() const;
	};
} // namespace lys
