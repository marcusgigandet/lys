/*
 * Copyright 2026 Marcus Gigandet
 *
 * All rights reserved.
 */

module lys:input_manager.impl;

import :input_manager;
import :input_map;
import mag;
import std;

namespace lys
{
	void InputManager::_processKeyCallback(const int key,
										   [[maybe_unused]] const int scancode,
										   const int action,
										   [[maybe_unused]] const int mods)
	{
		// Don't process invalid keys
		if (!isValidKey(static_cast<Key>(key)))
		{
			return;
		}

		const auto libKey{static_cast<Key>(key)};
		const auto libEdgeAction{static_cast<InputEdge>(action)};
		const InputEvent inputEvent{libKey, libEdgeAction};
		m_eventQueue.push(inputEvent);
	}

	void InputManager::_processMouseCallback(const double xPosIn, const double yPosIn)
	{
		// Initialize mouse position on first callback to avoid a large initial delta.
		static bool isFirstTime{true};
		if (isFirstTime)
		{
			m_mousePos = {xPosIn, yPosIn};
			m_mouseDelta = {};
			isFirstTime = false;
		}
		else
		{
			// Accumulate per-frame mouse movement
			const Vec2f posIn{xPosIn, yPosIn};
			m_mouseDelta += posIn - m_mousePos;
			m_mousePos = posIn;
		}
	}

	void InputManager::_processMouseButtonCallback(const int key, const int action, const int mods)
	{
		// Don't process invalid keys
		if (!isValidKey(static_cast<Key>(key)))
		{
			return;
		}

		const auto libKey{static_cast<Key>(key)};
		const auto libEdgeAction{static_cast<InputEdge>(action)};
		const InputEvent inputEvent{libKey, libEdgeAction};
		m_eventQueue.push(inputEvent);
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
} // namespace lys
