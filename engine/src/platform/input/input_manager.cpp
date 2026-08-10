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

module lys:input_manager.impl;

import :input_manager;
import :input_map;
import mag;
import std;

namespace lys
{
	void InputManager::_processKeyCallback(
		const int key, [[maybe_unused]] const int scancode, const int action,
		[[maybe_unused]] const int mods)
	{
		// Don't process invalid keys
		if (!isValidKey(static_cast<Key>(key)))
		{
			return;
		}

		const auto		 libKey{static_cast<Key>(key)};
		const auto		 libEdgeAction{static_cast<InputEdge>(action)};
		const InputEvent inputEvent{
			.key  = libKey,
			.edge = libEdgeAction,
		};
		m_eventQueue.push(inputEvent);

		if (m_dispatchEvents)
		{
			emitKeyEvent({
				.key	  = libKey,
				.scancode = scancode,
				.action	  = libEdgeAction,
				.mods	  = mods,
			});
		}
	}

	void InputManager::_processMouseCallback(const double xPosIn, const double yPosIn)
	{
		const Vec2f posIn{xPosIn, yPosIn};
		Vec2f		delta{};

		if (!m_hasMousePosition)
		{
			m_hasMousePosition = true;
			m_mousePos		   = posIn;
		}
		else
		{
			delta = posIn - m_mousePos;
			m_mouseDelta += delta;
			m_mousePos = posIn;
		}

		if (m_dispatchEvents)
		{
			emitMouseMoveEvent({
				.position = m_mousePos,
				.delta	  = delta,
			});
		}
	}

	void InputManager::_processMouseButtonCallback(const int key, const int action, const int mods)
	{
		// Don't process invalid keys
		if (!isValidKey(static_cast<Key>(key)))
		{
			return;
		}

		const auto		 libKey{static_cast<Key>(key)};
		const auto		 libEdgeAction{static_cast<InputEdge>(action)};
		const InputEvent inputEvent{
			.key  = libKey,
			.edge = libEdgeAction,
		};
		m_eventQueue.push(inputEvent);

		if (m_dispatchEvents)
		{
			emitMouseButtonEvent({
				.button = libKey,
				.action = libEdgeAction,
				.mods	= mods,
			});
		}
	}

	void InputManager::addKeyEventListener(KeyEventCallback callback)
	{
		m_keyListeners.push_back(std::move(callback));
	}

	void InputManager::addMouseButtonListener(MouseButtonEventCallback callback)
	{
		m_mouseButtonListeners.push_back(std::move(callback));
	}

	void InputManager::addMouseMoveListener(MouseMoveEventCallback callback)
	{
		m_mouseMoveListeners.push_back(std::move(callback));
	}

	void InputManager::enableEventDispatch() noexcept
	{
		m_dispatchEvents = true;
	}

	void InputManager::update() noexcept
	{
		m_mouseDelta = {}; // Reset the delta per-update call

		updateEventStates();
		processQueuedEvents();
	}

	bool InputManager::isPressed(const Key key) const noexcept
	{
		if (!m_events.contains(key))
		{
			return false;
		}

		const auto event{m_events.at(key)};
		return event.state == Pressed;
	}

	bool InputManager::isJustPressed(const Key key) const noexcept
	{
		if (!m_events.contains(key))
		{
			return false;
		}

		const auto event{m_events.at(key)};
		return event.state == JustPressed;
	}

	bool InputManager::isDown(const Key key) const noexcept
	{
		if (!m_events.contains(key))
		{
			return false;
		}

		const auto event{m_events.at(key)};
		return event.state == Pressed || event.state == JustPressed;
	}

	bool InputManager::isReleased(const Key key) const noexcept
	{
		if (!m_events.contains(key))
		{
			return false;
		}

		const auto event{m_events.at(key)};
		return event.state == Released;
	}

	bool InputManager::isJustReleased(const Key key) const noexcept
	{
		if (!m_events.contains(key))
		{
			return false;
		}

		const auto event{m_events.at(key)};
		return event.state == JustReleased;
	}

	bool InputManager::isUp(const Key key) const noexcept
	{
		if (!m_events.contains(key))
		{
			return false;
		}

		const auto event{m_events.at(key)};
		return event.state == Released || event.state == JustReleased;
	}

	bool InputManager::isRepeated(const Key key) const noexcept
	{
		if (!m_events.contains(key))
		{
			return false;
		}

		const auto event{m_events.at(key)};
		return event.repeat;
	}

	void InputManager::processQueuedEvents() noexcept
	{
		// Process all new input events
		while (!m_eventQueue.empty())
		{
			auto [key, edge]{m_eventQueue.front()};
			m_eventQueue.pop();

			// Modify in-place
			auto& event{m_events[key]};

			switch (edge)
			{
			case InputEdge::Press:
				if (event.state == InputState::Released || event.state == InputState::JustReleased)
				{
					event.state = InputState::JustPressed;
				}
				else
				{
					event.state = InputState::Pressed;
				}

				event.repeat = false;
				break;

			case InputEdge::Release:
				if (event.state == InputState::Pressed || event.state == InputState::JustPressed)
				{
					event.state = InputState::JustReleased;
				}
				else
				{
					event.state = InputState::Released;
				}

				event.repeat = false;
				break;

			case InputEdge::Repeat:
				event.repeat = true;
				break;
			}
		}
	}

	void InputManager::updateEventStates() noexcept
	{
		// Update the input states for each event and erase released keys
		for (auto it = m_events.begin(); it != m_events.end();)
		{
			// Advance transient states
			switch (it->second.state)
			{
			case InputState::JustPressed:
				it->second.state = InputState::Pressed;
				break;
			case InputState::JustReleased:
				it->second.state = InputState::Released;
				break;
			default:
				break;
			}

			// Erase if fully released
			if (it->second.state == InputState::Released)
			{
				it = m_events.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	void InputManager::emitKeyEvent(const KeyInputEvent& event) const
	{
		for (const auto& callback : m_keyListeners)
		{
			callback(event);
		}
	}

	void InputManager::emitMouseButtonEvent(const MouseButtonInputEvent& event) const
	{
		for (const auto& callback : m_mouseButtonListeners)
		{
			callback(event);
		}
	}

	void InputManager::emitMouseMoveEvent(const MouseMoveEvent& event) const
	{
		for (const auto& callback : m_mouseMoveListeners)
		{
			callback(event);
		}
	}
} // namespace lys
