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
export module lys:metal_command_buffer.impl;

import :rhi_command_buffer;
import :metal_command_buffer;
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
		m_commandBuffer->endCommandBuffer();
	}

	void CommandBuffer::commit()
	{
		const MTL4::CommandBuffer* buf{m_commandBuffer.get()};
		m_commandQueue.commit(&buf, 1);
	}

	void CommandBuffer::generateMipmaps(const rhi::Texture& texture)
	{
		// Generate mipmaps
		const auto commandAllocator{m_device.newCommandAllocator()};
		const auto commandBuffer{m_device.newCommandBuffer()};
		commandBuffer->beginCommandBuffer(commandAllocator);

		// Use an encoder to generate mipmaps
		const auto computeCommandEncoder{commandBuffer->computeCommandEncoder()};
		computeCommandEncoder->generateMipmaps(static_cast<const Texture&>(texture).texture());
		computeCommandEncoder->endEncoding();

		// Commit the command buffer to the command queue
		commandBuffer->endCommandBuffer();
		m_commandQueue.commit(&commandBuffer, 1);


		// Free memory
		computeCommandEncoder->release();
		commandBuffer->release();
		commandAllocator->release();
	}
} // namespace lys::mtl
