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
module lys:metal_render_pass_encoder.impl;

import :metal_argument_table;
import :metal_buffer;
import :metal_pipeline_state;
import :metal_render_pass_encoder;
import :metal_texture;
import :metal_types;
import std;

namespace lys::mtl
{
	RenderPassEncoder::RenderPassEncoder(MTL::Device& device, MTL4::RenderCommandEncoder* encoder) :
		Object(device), rhi::RenderPassEncoder(), m_encoder(NS::TransferPtr(encoder))
	{
	}

	void RenderPassEncoder::setPipeline(const rhi::RenderPipelineState& state)
	{
		if (!m_encoder)
		{
			return;
		}

		const auto& mtlState{static_cast<const RenderPipelineState&>(state)};
		m_encoder->setRenderPipelineState(mtlState.renderPipelineState());
		m_encoder->setCullMode(toMetalEnum(mtlState.desc().cullMode));
		m_encoder->setFrontFacingWinding(toMetalEnum(mtlState.desc().winding));

		if (mtlState.depthStencilState())
		{
			m_encoder->setDepthStencilState(mtlState.depthStencilState());
		}
	}

	RenderPassEncoder& RenderPassEncoder::setResource(
		const rhi::ShaderStage stage, const rhi::Buffer& buffer, const std::string& name)
	{
		// Todo: Resolve names using shader reflection.
		return *this;
	}

	RenderPassEncoder& RenderPassEncoder::setResource(
		const rhi::ShaderStage stage, const rhi::Texture& texture, const std::string& name)
	{
		// Todo: Resolve names using shader reflection.
		return *this;
	}

	RenderPassEncoder& RenderPassEncoder::setResource(
		const rhi::ShaderStage stage, const rhi::Buffer& buffer, const std::uint32_t index)
	{
		const auto table{argumentTable()};
		if (!table || rhi::ShaderStage::Compute == stage)
		{
			return *this;
		}

		table->setAddress(static_cast<const Buffer&>(buffer).buffer()->gpuAddress(), index);
		bindArgumentTable(stage);
		return *this;
	}

	RenderPassEncoder& RenderPassEncoder::setResource(
		const rhi::ShaderStage stage, const rhi::Texture& texture, const std::uint32_t index)
	{
		const auto table{argumentTable()};
		if (!table || rhi::ShaderStage::Compute == stage)
		{
			return *this;
		}

		table->setTexture(static_cast<const Texture&>(texture).texture()->gpuResourceID(), index);
		bindArgumentTable(stage);
		return *this;
	}

	void RenderPassEncoder::draw(const rhi::PrimitiveType primitiveType, const rhi::DrawDesc& desc)
	{
		if (!m_encoder || desc.vertexCount == 0 || desc.instanceCount == 0)
		{
			return;
		}

		m_encoder->drawPrimitives(
			toMetalEnum(primitiveType),
			desc.firstVertex,
			desc.vertexCount,
			desc.instanceCount,
			desc.firstInstance);
	}

	void RenderPassEncoder::end()
	{
		if (m_encoder)
		{
			m_encoder->endEncoding();
			m_encoder.reset();
			m_argumentTable.reset();
		}
	}

	MTL4::ArgumentTable* RenderPassEncoder::argumentTable()
	{
		if (!m_argumentTable && m_encoder)
		{
			m_argumentTable = createArgumentTable(m_device);
		}

		return m_argumentTable.get();
	}

	void RenderPassEncoder::bindArgumentTable(const rhi::ShaderStage stage) const
	{
		const auto renderStage =
			stage == rhi::ShaderStage::Vertex ? MTL::RenderStageVertex : MTL::RenderStageFragment;
		m_encoder->setArgumentTable(m_argumentTable.get(), renderStage);
	}
} // namespace lys::mtl
