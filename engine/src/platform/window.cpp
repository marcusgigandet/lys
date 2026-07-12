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

	Window::Window(const WindowDesc& desc) : m_desc(desc) { initWindow(); }

	void Window::initWindow()
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
		const GLFWwindow* window = glfwCreateWindow(m_desc.dimensions.x,
													m_desc.dimensions.y,
													m_desc.title.c_str(),
													nullptr,
													nullptr);

		if (!window)
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
} // namespace lys
