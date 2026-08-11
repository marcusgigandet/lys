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

module lys:rhi_device.impl;

import :rhi_device;
import std;

#ifdef LYS_VULKAN
import :vulkan_device;
#endif

#ifdef LYS_METAL
import :metal_device;
#endif

namespace lys::rhi
{
	Device::Device(const DeviceDesc& desc) : m_desc(desc)
	{
	}

	CommandQueue& Device::queue(const CommandQueueType type)
	{
		const auto index{static_cast<std::size_t>(type)};
		auto&	   queue{m_commandQueues[index]};

		// Check if the queue is null
		if (!queue)
		{
			// Creat a new queue instance
			queue = createCommandQueue(type);
		}

		return *queue;
	}

	std::unique_ptr<Device> createDevice(const DeviceDesc& desc)
	{
		switch (desc.backend)
		{
		case Backend::Auto:
#if defined(LYS_VULKAN) && defined(LYS_METAL)
#	ifdef __APPLE__
			return std::make_unique<mtl::Device>(desc);
#	else
			return std::make_unique<vk::Device>(desc);
#	endif
#elifdef LYS_VULKAN
			return std::make_unique<vk::Device>(desc);
#elifdef LYS_METAL
			return std::make_unique<mtl::Device>(desc);
#else
			throw std::runtime_error("No RHI backend available.");
#endif

		case Backend::Vulkan:
#ifdef LYS_VULKAN
			return std::make_unique<vk::Device>(desc);
#else
			throw std::runtime_error("Vulkan backend is not enabled in this build.");
#endif

		case Backend::Metal:
#ifdef LYS_METAL
			return std::make_unique<mtl::Device>(desc);
#else
			throw std::runtime_error("Metal backend is not enabled in this build.");
#endif

		default:
			throw std::runtime_error("Invalid RHI backend selection.");
		}
	}
} // namespace lys::rhi
