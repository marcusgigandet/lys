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

export module lys:input_manager;

import :input_map;
import mag;
import std;

namespace lys
{
	/**
	 * @brief Manages keyboard and mouse input state for the application.
	 *
	 * Handles raw input events from GLFW, processes them into logical states,
	 * and provides query methods for current input state. Supports both immediate
	 * and frame-based input polling with state tracking for pressed/released events.
	 */
	export class InputManager
	{
		/* Event queues and management */
		std::queue<InputEvent>					   m_eventQueue{}; ///< New, unprocessed events
		std::unordered_map<Key, LogicalInputEvent> m_events; ///< Current collection of key events

		/* Mouse related data */
		Vec2f m_mouseDelta{}; ///< Change in mouse position since last frame
		Vec2f m_mousePos{};	  ///< Current mouse position

	public:
		/**
		 * @brief Internally called by GLFW when a key event occurs.
		 *
		 * Adds a new input event to a queue to be processed on the next update.
		 *
		 * @param key The key that was pressed or released.
		 * @param scancode The system-specific scancode of the key.
		 * @param action The action (press, release, repeat).
		 * @param mods Bit field describing which modifier keys were held down.
		 */
		void _processKeyCallback(int key, int scancode, int action, int mods);

		/**
		 * @brief Internally called by GLFW when the mouse moves.
		 *
		 * @param xPosIn The new X position of the mouse.
		 * @param yPosIn The new Y position of the mouse.
		 */
		void _processMouseCallback(double xPosIn, double yPosIn);

		/**
		 * @brief Internally called by GLFW when a mouse button is pressed.
		 *
		 * @param key The key that was pressed or released.
		 * @param action The action (press, release, repeat).
		 * @param mods Bit field describing which modifier keys were held down.
		 */
		void _processMouseButtonCallback(int key, int action, int mods);

		/**
		 * @brief Updates input states and processes queued events.
		 *
		 * - Resets mouse delta.
		 * - Advances transient states (JustPressed -> Pressed, JustReleased -> Released).
		 * - Removes fully released events.
		 * - Processes queued events: updates state and repeat flags.
		 *
		 * @note Ensure this is called once per frame to keep the events up-to-date.
		 */
		void update() noexcept;

		[[nodiscard]] bool isPressed(Key key) const noexcept;
		[[nodiscard]] bool isJustPressed(Key key) const noexcept;

		[[nodiscard]] bool isDown(Key key) const noexcept;

		[[nodiscard]] bool isReleased(Key key) const noexcept;
		[[nodiscard]] bool isJustReleased(Key key) const noexcept;

		[[nodiscard]] bool isUp(Key key) const noexcept;

		[[nodiscard]] bool isRepeated(Key key) const noexcept;

		/**
		 * @return Returns mouse movement since last update.
		 */
		[[nodiscard]] Vec2f mouseDelta() const noexcept { return m_mouseDelta; }

		/**
		 * @return Returns current mouse position.
		 */
		[[nodiscard]] Vec2f mousePosition() const noexcept { return m_mousePos; }

	private:
		/**
		 * @brief Processes all events in the current queue.
		 *
		 * Converts raw events to logical states and updates the event map.
		 */
		void processQueuedEvents() noexcept;

		/**
		 * @brief Updates the state of each event in the current collection.
		 *
		 * Handles state transitions (JustPressed -> Pressed, etc.) and cleanup.
		 */
		void updateEventStates() noexcept;
	};
} // namespace lys
