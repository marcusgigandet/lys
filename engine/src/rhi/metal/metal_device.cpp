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
#include <Metal/Metal.hpp>
module lys:metal_device.impl;

import :metal_buffer;
import :metal_command_buffer;
import :metal_command_queue;
import :metal_device;
import :metal_pipeline_state;
import :metal_shader;
import :metal_surface;
import :metal_swapchain;
import :metal_texture;
import std;

namespace lys::mtl
{
	Device::Device(const rhi::DeviceDesc& desc) :
		rhi::Device(desc), m_device(NS::TransferPtr(MTL::CreateSystemDefaultDevice()))
	{
	}

	std::unique_ptr<rhi::CommandQueue> Device::createCommandQueue(const rhi::CommandQueueType type)
	{
		return std::make_unique<CommandQueue>(*m_device.get(), type);
	}

	std::unique_ptr<rhi::CommandBuffer> Device::createCommandBuffer()
	{
		return std::make_unique<CommandBuffer>(
			*m_device.get(),
			*static_cast<CommandQueue&>(transferQueue()).commandQueue());
	}

	std::unique_ptr<rhi::Buffer> Device::createBuffer(const rhi::BufferDesc& desc)
	{
		return std::make_unique<Buffer>(*m_device.get(), desc);
	}

	std::unique_ptr<rhi::Texture> Device::createTexture(const rhi::TextureDesc& desc)
	{
		return std::make_unique<Texture>(*m_device.get(), desc);
	}

	std::unique_ptr<rhi::Shader> Device::createShader(const rhi::ShaderDesc& desc)
	{
		return std::make_unique<Shader>(*m_device.get(), desc);
	}

	std::unique_ptr<rhi::RenderPipelineState>
	Device::createRenderPipeline(const rhi::RenderPipelineDesc& desc)
	{
		return std::make_unique<RenderPipelineState>(*m_device.get(), desc);
	}

	std::unique_ptr<rhi::ComputePipelineState>
	Device::createComputePipeline(const rhi::ComputePipelineDesc& desc)
	{
		return std::make_unique<ComputePipelineState>(*m_device.get(), desc);
	}

	std::unique_ptr<rhi::Surface> Device::createSurface(const Window& window)
	{
		return std::make_unique<Surface>(*m_device.get(), window);
	}

	std::unique_ptr<rhi::Swapchain>
	Device::createSwapchain(rhi::Surface& surface, const rhi::SwapchainDesc& desc)
	{
		auto& metalSurface{static_cast<Surface&>(surface)};
		return std::make_unique<Swapchain>(metalSurface, desc);
	}
} // namespace lys::mtl
