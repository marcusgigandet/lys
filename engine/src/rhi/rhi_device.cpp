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

#if defined(LYS_VULKAN)
import :vulkan_device;
#endif

#if defined(LYS_METAL)
import :metal_device;
#endif

namespace lys
{
	RHIDevice::RHIDevice(const RHIDeviceDesc& desc) : m_desc(desc)
	{
	}

	std::unique_ptr<Buffer> RHIDevice::createBufferImpl([[maybe_unused]] const BufferDesc& desc)
	{
		throw std::runtime_error("Unimplemented function");
	}

	std::unique_ptr<Texture> RHIDevice::createTextureImpl([[maybe_unused]] const TextureDesc& desc)
	{
		throw std::runtime_error("Unimplemented function");
	}

	std::unique_ptr<Shader> RHIDevice::createShaderImpl([[maybe_unused]] const ShaderDesc& desc)
	{
		throw std::runtime_error("Unimplemented function");
	}

	std::unique_ptr<GraphicsPipelineState>
	RHIDevice::createGraphicsPipelineImpl([[maybe_unused]] const GraphicsPipelineDesc& desc)
	{
		throw std::runtime_error("Unimplemented function");
	}

	std::unique_ptr<ComputePipelineState>
	RHIDevice::createComputePipelineImpl([[maybe_unused]] const ComputePipelineDesc& desc)
	{
		throw std::runtime_error("Unimplemented function");
	}

	CommandQueue& RHIDevice::queue(const CommandQueueType type)
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

	std::unique_ptr<RHIDevice> createRHIDevice(const RHIDeviceDesc& desc)
	{
		switch (desc.backend)
		{
		case RHIBackend::Auto:
#if defined(LYS_VULKAN) && defined(LYS_METAL)
#	ifdef __APPLE__
			return std::make_unique<MetalDevice>(desc);
#	else
			return std::make_unique<VulkanDevice>(desc);
#	endif
#elif defined(LYS_VULKAN)
			return std::make_unique<VulkanDevice>(desc);
#elif defined(LYS_METAL)
			return std::make_unique<MetalDevice>(desc);
#else
			throw std::runtime_error("No RHI backend available.");
#endif

		case RHIBackend::Vulkan:
#if defined(LYS_VULKAN)
			return std::make_unique<VulkanDevice>(desc);
#else
			throw std::runtime_error("Vulkan backend is not enabled in this build.");
#endif

		case RHIBackend::Metal:
#if defined(LYS_METAL)
			return std::make_unique<MetalDevice>(desc);
#else
			throw std::runtime_error("Metal backend is not enabled in this build.");
#endif

		default:
			throw std::runtime_error("Invalid RHI backend selection.");
		}
	}
} // namespace lys
