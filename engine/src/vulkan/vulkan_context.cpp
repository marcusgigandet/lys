/*
 * Copyright 2026 Marcus Gigandet
 *
 * All rights reserved.
 */

module;
#include <GLFW/glfw3.h>
module lys:vulkan_context.impl;

import :vulkan_context;
import :vulkan_debug;
import vulkan;
import std;

namespace lys
{
	VulkanContext::VulkanContext()
	{
		m_instance = createInstance(m_context);
		const vk::raii::PhysicalDevice physicalDevice{
			m_instance.enumeratePhysicalDevices().front()};
		vk::raii::Device device(physicalDevice, vk::DeviceCreateInfo{});
	}

	vk::raii::Instance VulkanContext::createInstance(const vk::raii::Context& context)
	{
		if (enableValidationLayers)
		{
			std::vector<char const*> requiredLayers;
			requiredLayers.assign(validationLayers.begin(), validationLayers.end());
		}

		vk::ApplicationInfo appInfo{
			.pApplicationName = "Lys Engine",
			.applicationVersion = vk::makeVersion(1, 0, 0),
			.pEngineName = "Lys Engine",
			.engineVersion = vk::makeVersion(1, 0, 0),
			.apiVersion = context.enumerateInstanceVersion(),
		};

		std::uint32_t glfwExtensionCount{0};
		auto glfwExtensions{glfwGetRequiredInstanceExtensions(&glfwExtensionCount)};

		// Check if the required GLFW extensions are supported by the Vulkan implementation
		auto extensionProperties{context.enumerateInstanceExtensionProperties()};
		for (uint32_t i{0}; i < glfwExtensionCount; ++i)
		{
			if (std::ranges::none_of(
					extensionProperties,
					[glfwExtension = glfwExtensions[i]](auto const& extensionProperty)
					{ return strcmp(extensionProperty.extensionName, glfwExtension) == 0; }))
			{
				throw std::runtime_error("Required GLFW extension not supported: " +
										 std::string(glfwExtensions[i]));
			}
		}

		const vk::InstanceCreateInfo instanceCreateInfo{
			.pApplicationInfo = &appInfo,
			.enabledLayerCount = glfwExtensionCount,
			.ppEnabledLayerNames = glfwExtensions,
			.enabledExtensionCount = 0,
			.ppEnabledExtensionNames = nullptr,
		};

		vk::raii::Instance instance(context, instanceCreateInfo);

		return instance;
	}

	vk::raii::Device VulkanContext::createDevice(const vk::raii::PhysicalDevice& physicalDevice,
												 const vk::DeviceCreateInfo& deviceCreateInfo)
	{
		vk::raii::Device device(physicalDevice, deviceCreateInfo);

		return device;
	}

	std::vector<const char*> VulkanContext::requiredVulkanInstanceExtensions()
	{
		std::uint32_t glfwExtensionCount{0};
		const auto glfwExtensions{glfwGetRequiredInstanceExtensions(&glfwExtensionCount)};

		std::vector extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
		if (enableValidationLayers)
		{
			extensions.push_back(vk::EXTDebugUtilsExtensionName);
		}

		return extensions;
	}
} // namespace lys
