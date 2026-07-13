/*
 * Copyright 2026 Marcus Gigandet
 *
 * All rights reserved.
 */

module;
module lys:vulkan_context.impl;

import :vulkan_context;
import vulkan;
import std;

namespace lys
{
	VulkanContext::VulkanContext() {}

	vk::raii::Instance VulkanContext::createInstance(const vk::raii::Context& context)
	{
		vk::ApplicationInfo appInfo{
			.pApplicationName = "Lys Engine",
			.applicationVersion = vk::makeVersion(1, 0, 0),
			.pEngineName = "Lys Engine",
			.engineVersion = vk::makeVersion(1, 0, 0),
			.apiVersion = context.enumerateInstanceVersion(),
		};

		const vk::InstanceCreateInfo instanceCreateInfo{
			.pApplicationInfo = &appInfo,
			.enabledLayerCount = 0,
			.ppEnabledLayerNames = nullptr,
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
} // namespace lys
