/*
 * Copyright 2026 Marcus Gigandet
 *
 * All rights reserved.
 */

module;
#include <GLFW/glfw3.h>
export module lys:vulkan_context;

import std;
import vulkan;

namespace lys
{
	export class VulkanContext
	{
		vk::raii::Context m_context;
		vk::raii::Instance m_instance{nullptr};

	public:
		VulkanContext();

	private:
		[[nodiscard]] static vk::raii::Instance createInstance(const vk::raii::Context& context);

		[[nodiscard]] static vk::raii::Device
		createDevice(const vk::raii::PhysicalDevice& physicalDevice,
					 const vk::DeviceCreateInfo& deviceCreateInfo);

		[[nodiscard]] std::vector<const char*> requiredVulkanInstanceExtensions() const;
		[[nodiscard]] vk::raii::SurfaceKHR createVulkanSurface(vk::raii::Instance instance) const;
	};
} // namespace lys
