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
		std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_prevTime;

	public:
		/**
		 * @brief Resets the timer to the current time.
		 *
		 * Sets both `m_start` and `m_prevTime` to the current time,
		 * effectively starting or restarting the timer.
		 */
		void start();

		/**
		 * @brief Gets the time elapsed since the last call to `delta()`.
		 *
		 * Updates `m_prevTime` to the current time, preparing for the next `delta()` call.
		 * Use this method to measure frame time in game loops.
		 *
		 * @return The time (in seconds) since the last call to `delta()`.
		 */
		[[nodiscard]] double delta();

		/**
		 * @brief Gets the time since the last `delta()` call without updating the timer.
		 *
		 * Unlike `delta()`, this method does not modify `m_prevTime`.
		 * Useful for checking the current frame time without affecting future calls.
		 *
		 * @return The time (in seconds) since the last `delta()` call.
		 */
		[[nodiscard]] double peekDelta() const;

		/**
		 * @brief Gets the total time elapsed since the timer was started or reset.
		 *
		 * Updates `m_prevTime` to the current time, preparing for the next `delta()` call.
		 * Use this method to measure the total elapsed time.
		 *
		 * @return The total time (in seconds) since the timer was started.
		 */
		[[nodiscard]] double elapsed();

		/**
		 * @brief Gets the total time elapsed since the timer was started, without updating the
		 * timer.
		 *
		 * Unlike `elapsed()`, this method does not modify `m_prevTime`.
		 * Useful for checking the total elapsed time without affecting future calls.
		 *
		 * @return The total time (in seconds) since the timer was started.
		 */
		[[nodiscard]] double peekElapsed() const;
	};
} // namespace lys
