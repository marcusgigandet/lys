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
#include <spdlog/spdlog.h>
export module lys:metal_command_buffer.impl;

import :metal_buffer;
import :metal_command_buffer;
import :metal_pipeline_state;
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
		m_commandBuffer->endCommandBuffer();
	}

	void CommandBuffer::beginComputePass()
	{
		m_computeCommandEncoder = NS::TransferPtr(m_commandBuffer->computeCommandEncoder());
	}

	void CommandBuffer::beginRenderPass(const rhi::RenderPassDesc& desc)
	{
		const auto descriptor{NS::TransferPtr(MTL4::RenderPassDescriptor::alloc()->init())};

		// Configure the depth attachment
		if (desc.depthAttachmentDesc.has_value())
		{
			const auto [loadAction]{desc.depthAttachmentDesc.value()};
			const auto depthDescriptor{
				NS::TransferPtr(MTL::RenderPassDepthAttachmentDescriptor::alloc()->init())};
			depthDescriptor->setLoadAction(toMetalEnum(loadAction));

			// Set the depth attachment on the render pass
			descriptor->setDepthAttachment(depthDescriptor.get());
		}

		// Configure the render pass
		m_renderCommandEncoder =
			NS::TransferPtr(m_commandBuffer->renderCommandEncoder(descriptor.get()));
	}

	void CommandBuffer::endComputePass()
	{
		m_computeCommandEncoder->endEncoding();
	}

	void CommandBuffer::endRenderPass()
	{
		m_renderCommandEncoder->endEncoding();
	}

	void CommandBuffer::setComputePipelineState(const rhi::ComputePipelineState& state)
	{
		if (!m_computeCommandEncoder)
		{
			return;
		}

		m_computeCommandEncoder->setComputePipelineState(
			static_cast<const ComputePipelineState&>(state).computePipelineState());
	}

	void CommandBuffer::setRenderPipelineState(const rhi::RenderPipelineState& state)
	{
		if (!m_renderCommandEncoder)
		{
			return;
		}

		const auto& mtlState = static_cast<const RenderPipelineState&>(state);

		m_renderCommandEncoder->setRenderPipelineState(mtlState.renderPipelineState());
		m_renderCommandEncoder->setCullMode(toMetalEnum(mtlState.desc().cullMode));
		m_renderCommandEncoder->setFrontFacingWinding(toMetalEnum(mtlState.desc().winding));

		if (mtlState.depthStencilState())
		{
			m_renderCommandEncoder->setDepthStencilState(mtlState.depthStencilState());
		}
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

	CommandBuffer& CommandBuffer::setResource(
		const rhi::ShaderStage stage, const rhi::Buffer& buffer, const std::string& name)
	{
		// Return early if the encoder is null
		if (!isEncoderValid(stage))
		{
			return *this;
		}

		return *this;
	}

	CommandBuffer& CommandBuffer::setResource(
		const rhi::ShaderStage stage, const rhi::Texture& texture, const std::string& name)
	{
		// Return early if the encoder is null
		if (!isEncoderValid(stage))
		{
			return *this;
		}

		return *this;
	}

	CommandBuffer& CommandBuffer::setResource(
		const rhi::ShaderStage stage, const rhi::Buffer& buffer, std::uint32_t index)
	{
		// Return early if the encoder is null
		if (!isEncoderValid(stage))
		{
			return *this;
		}

		const auto argumentTable{makeArgumentTable()};
		argumentTable->setAddress(static_cast<const Buffer&>(buffer).buffer()->gpuAddress(), index);
		m_renderCommandEncoder->setArgumentTable(
			argumentTable,
			MTL::RenderStageFragment | MTL::RenderStageVertex);

		return *this;
	}

	CommandBuffer& CommandBuffer::setResource(
		const rhi::ShaderStage stage, const rhi::Texture& texture, std::uint32_t index)
	{
		// Return early if the encoder is null
		if (!isEncoderValid(stage))
		{
			return *this;
		}

		const auto argumentTable{makeArgumentTable()};
		argumentTable->setTexture(
			static_cast<const Texture&>(texture).texture()->gpuResourceID(),
			index);
		m_renderCommandEncoder->setArgumentTable(
			argumentTable,
			MTL::RenderStageFragment | MTL::RenderStageVertex);

		return *this;
	}

	MTL4::ArgumentTable* CommandBuffer::makeArgumentTable() const
	{
		NS::Error* nsError;
		const auto argumentTableDescriptor{MTL4::ArgumentTableDescriptor::alloc()->init()};

		// Todo: Make this use maxFramesInFlight
		argumentTableDescriptor->setMaxBufferBindCount(3);

		// Create the argument table
		const auto argumentTable{m_device.newArgumentTable(argumentTableDescriptor, &nsError)};
		argumentTableDescriptor->release();

		if (nsError)
		{
			SPDLOG_DEBUG(
				std::format(
					"An error occurred when constructing an MTL4::ArgumentTable : {}",
					nsError->description()->cString(NS::UTF8StringEncoding)));
			argumentTable->release();
			return nullptr;
		}

		return argumentTable;
	}

	bool CommandBuffer::isEncoderValid(const rhi::ShaderStage stage) const
	{
		if (rhi::ShaderStage::Compute == stage)
		{
			return nullptr != m_computeCommandEncoder.get();
		}
		else
		{
			return nullptr != m_renderCommandEncoder.get();
		}
	}
} // namespace lys::mtl
