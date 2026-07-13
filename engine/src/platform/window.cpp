/*
 * Copyright 2026 Marcus Gigandet
 *
 * All rights reserved.
 */

module;
#include <GLFW/glfw3.h>
module lys:window.impl;

import :log;
import :window;
import std;

namespace lys
{
	Window::Window() { initWindow(); }

	Window::Window(const WindowDesc& desc) { initWindow(desc); }

	Window::~Window() { destroyWindow(); }

	void Window::initWindow(const WindowDesc& desc)
	{
		if (!s_glfwInitialized)
		{
			initGLFW();
		}

		if (!glfwVulkanSupported())
		{
			throw std::runtime_error("Vulkan is not supported.");
		}

		// Configure window for Vulkan
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

		// Create window instance and verify that it was successfully created
		m_glfwWindow = glfwCreateWindow(desc.dimensions.x,
										desc.dimensions.y,
										desc.title.c_str(),
										nullptr,
										nullptr);

		if (!m_glfwWindow)
		{
			glfwTerminate();
			throw std::runtime_error("Failed to create window.");
		}
	}

	void Window::initGLFW()
	{
		m_glfwWindow = nullptr;
		if (GLFW_FALSE == glfwInit())
		{
			throw std::runtime_error("Failed to initialize GLFW!");
		}
	}

	void Window::destroyWindow() const { glfwDestroyWindow(m_glfwWindow); }


	void Window::keyCallback(GLFWwindow* window,
							 const int key,
							 const int scancode,
							 const int action,
							 const int mods)
	{
		if (const auto self = static_cast<Window*>(glfwGetWindowUserPointer(window)))
		{
			if (self->m_keyCallback)
			{
				self->m_keyCallback(key, scancode, action, mods);
			}
		}
	}

	void Window::mouseButtonCallback(GLFWwindow* window,
									 const int button,
									 const int action,
									 const int mods)
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
