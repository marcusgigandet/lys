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
module lys:metal_command_buffer.impl;

import :metal_command_buffer;
import :metal_compute_pass_encoder;
import :metal_render_pass_encoder;
import :metal_texture;
import :metal_types;
import :rhi_command_buffer;
import std;

namespace lys::mtl
{
	CommandBuffer::CommandBuffer(MTL::Device& device, MTL4::CommandQueue& commandQueue) :
		Object(device), rhi::CommandBuffer(), m_commandQueue(commandQueue)
	{
		m_commandAllocator = NS::TransferPtr(m_device.newCommandAllocator());
		m_commandBuffer	   = NS::TransferPtr(m_device.newCommandBuffer());
	}

	void CommandBuffer::begin()
	{
		m_commandBuffer->beginCommandBuffer(m_commandAllocator.get());
	}

	void CommandBuffer::end()
	{
		endActivePass();
		m_commandBuffer->endCommandBuffer();
	}

	rhi::ComputePassEncoder& CommandBuffer::beginComputePass()
	{
		endActivePass();
		m_computePassEncoder = std::make_unique<ComputePassEncoder>(
			m_device,
			m_commandBuffer->computeCommandEncoder());
		return *m_computePassEncoder;
	}

	rhi::RenderPassEncoder& CommandBuffer::beginRenderPass(const rhi::RenderPassDesc& desc)
	{
		if (!desc.colorAttachment)
		{
			throw std::invalid_argument("A render pass requires a color attachment");
		}

		endActivePass();
		const auto descriptor{NS::TransferPtr(MTL4::RenderPassDescriptor::alloc()->init())};
		const auto colorAttachment{descriptor->colorAttachments()->object(0)};
		colorAttachment->setTexture(static_cast<const Texture&>(*desc.colorAttachment).texture());
		colorAttachment->setLoadAction(toMetalEnum(desc.loadAction));
		colorAttachment->setStoreAction(MTL::StoreActionStore);
		colorAttachment->setClearColor(
			MTL::ClearColor{
				desc.clearColor.x,
				desc.clearColor.y,
				desc.clearColor.z,
				desc.clearColor.w,
			});

		if (desc.depthAttachmentDesc.has_value())
		{
			const auto [loadAction]{desc.depthAttachmentDesc.value()};
			const auto depthDescriptor{
				NS::TransferPtr(MTL::RenderPassDepthAttachmentDescriptor::alloc()->init())};
			depthDescriptor->setLoadAction(toMetalEnum(loadAction));
			descriptor->setDepthAttachment(depthDescriptor.get());
		}

		m_renderPassEncoder = std::make_unique<RenderPassEncoder>(
			m_device,
			m_commandBuffer->renderCommandEncoder(descriptor.get()));
		return *m_renderPassEncoder;
	}

	void CommandBuffer::generateMipmaps(const rhi::Texture& texture)
	{
		const auto commandAllocator{m_device.newCommandAllocator()};
		const auto commandBuffer{m_device.newCommandBuffer()};
		commandBuffer->beginCommandBuffer(commandAllocator);

		const auto computeCommandEncoder{commandBuffer->computeCommandEncoder()};
		computeCommandEncoder->generateMipmaps(static_cast<const Texture&>(texture).texture());
		computeCommandEncoder->endEncoding();

		commandBuffer->endCommandBuffer();
		m_commandQueue.commit(&commandBuffer, 1);

		computeCommandEncoder->release();
		commandBuffer->release();
		commandAllocator->release();
	}

	void CommandBuffer::endActivePass()
	{
		if (m_renderPassEncoder)
		{
			m_renderPassEncoder->end();
			m_renderPassEncoder.reset();
		}

		if (m_computePassEncoder)
		{
			m_computePassEncoder->end();
			m_computePassEncoder.reset();
		}
	}
} // namespace lys::mtl
