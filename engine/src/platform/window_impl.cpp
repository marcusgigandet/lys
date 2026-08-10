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

module;
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
module lys:window.impl;

import :window;
import std;

namespace lys
{
	Window::Window()
	{
		initWindow();
	}

	Window::Window(const WindowDesc& desc)
	{
		initWindow(desc);
	}

	Window::~Window()
	{
		destroyWindow();
	}

	void Window::initWindow(const WindowDesc& desc)
	{
		if (!s_glfwInitialized)
		{
			initGLFW();
		}

		// Configure window for Vulkan
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

		// Create window instance and verify that it was successfully created
		m_glfwWindow = glfwCreateWindow(
			desc.dimensions.x,
			desc.dimensions.y,
			desc.title.c_str(),
			nullptr,
			nullptr);

		if (!m_glfwWindow)
		{
			glfwTerminate();
			throw std::runtime_error("Failed to create window.");
		}

		glfwSwapInterval(desc.vsync ? GLFW_TRUE : GLFW_FALSE);
		registerCallbacks();
	}

	void Window::initGLFW()
	{
		m_glfwWindow = nullptr;
		if (GLFW_FALSE == glfwInit())
		{
			throw std::runtime_error("Failed to initialize GLFW!");
		}

		spdlog::trace("Successfully initialized GLFW\n");
	}

	void Window::destroyWindow() const
	{
		glfwDestroyWindow(m_glfwWindow);
	}

	void Window::registerCallbacks()
	{
		m_keyCallback = [this](const int key, const int scancode, const int action, const int mods)
		{ m_inputManager._processKeyCallback(key, scancode, action, mods); };

		m_cursorPosCallback = [this](const double x, const double y)
		{ m_inputManager._processMouseCallback(x, y); };

		m_mouseButtonCallback = [this](const int key, const int action, const int mods)
		{ m_inputManager._processMouseButtonCallback(key, action, mods); };
	}

	void Window::keyCallback(
		GLFWwindow* window, const int key, const int scancode, const int action, const int mods)
	{
		if (const auto self = static_cast<Window*>(glfwGetWindowUserPointer(window)))
		{
			if (self->m_keyCallback)
			{
				self->m_keyCallback(key, scancode, action, mods);
			}
		}
	}

	void Window::mouseButtonCallback(
		GLFWwindow* window, const int button, const int action, const int mods)
	{
		if (const auto self = static_cast<Window*>(glfwGetWindowUserPointer(window)))
		{
			if (self->m_mouseButtonCallback)
			{
				self->m_mouseButtonCallback(button, action, mods);
			}
		}
	}

	void Window::cursorPosCallback(GLFWwindow* window, const double xPos, const double yPos)
	{
		if (const auto self = static_cast<Window*>(glfwGetWindowUserPointer(window)))
		{
			if (self->m_cursorPosCallback)
			{
				self->m_cursorPosCallback(xPos, yPos);
			}
		}
	}

	void Window::windowSizeCallback(GLFWwindow* window, const int width, const int height)
	{
		if (const auto self = static_cast<Window*>(glfwGetWindowUserPointer(window)))
		{
			if (self->m_windowSizeCallback)
			{
				self->m_windowSizeCallback(width, height);
			}
		}
	}

	void
	Window::windowFramebufferSizeCallback(GLFWwindow* window, const int width, const int height)
	{
		if (const auto self = static_cast<Window*>(glfwGetWindowUserPointer(window)))
		{
			if (self->m_windowFramebufferSizeCallback)
			{
				self->m_windowFramebufferSizeCallback(width, height);
			}
		}
	}
} // namespace lys
