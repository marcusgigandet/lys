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
module lys:metal_compute_pass_encoder.impl;

import :metal_argument_table;
import :metal_buffer;
import :metal_compute_pass_encoder;
import :metal_pipeline_state;
import :metal_texture;
import std;

namespace lys::mtl
{
	ComputePassEncoder::ComputePassEncoder(
		MTL::Device& device, MTL4::ComputeCommandEncoder* encoder) :
		Object(device), rhi::ComputePassEncoder(), m_encoder(NS::TransferPtr(encoder))
	{
	}

	void ComputePassEncoder::setPipeline(const rhi::ComputePipelineState& state)
	{
		if (m_encoder)
		{
			m_encoder->setComputePipelineState(
				static_cast<const ComputePipelineState&>(state).computePipelineState());
		}
	}

	ComputePassEncoder&
	ComputePassEncoder::setResource(const rhi::Buffer& buffer, const std::string& name)
	{
		// Todo: Resolve names using shader reflection.
		return *this;
	}

	ComputePassEncoder&
	ComputePassEncoder::setResource(const rhi::Texture& texture, const std::string& name)
	{
		// Todo: Resolve names using shader reflection.
		return *this;
	}

	ComputePassEncoder&
	ComputePassEncoder::setResource(const rhi::Buffer& buffer, const std::uint32_t index)
	{
		const auto table{argumentTable()};
		if (!table)
		{
			return *this;
		}

		table->setAddress(static_cast<const Buffer&>(buffer).buffer()->gpuAddress(), index);
		m_encoder->setArgumentTable(table);
		return *this;
	}

	ComputePassEncoder&
	ComputePassEncoder::setResource(const rhi::Texture& texture, const std::uint32_t index)
	{
		const auto table{argumentTable()};
		if (!table)
		{
			return *this;
		}

		table->setTexture(static_cast<const Texture&>(texture).texture()->gpuResourceID(), index);
		m_encoder->setArgumentTable(table);
		return *this;
	}

	void ComputePassEncoder::dispatch(const rhi::DispatchDesc& desc)
	{
		if (!m_encoder)
		{
			return;
		}

		const auto& threadCount{desc.threadCount};
		const auto& threadsPerGroup{desc.threadsPerGroup};
		m_encoder->dispatchThreads(
			MTL::Size{threadCount.x, threadCount.y, threadCount.z},
			MTL::Size{threadsPerGroup.x, threadsPerGroup.y, threadsPerGroup.z});
	}

	void ComputePassEncoder::end()
	{
		if (m_encoder)
		{
			m_encoder->endEncoding();
			m_encoder.reset();
			m_argumentTable.reset();
		}
	}

	MTL4::ArgumentTable* ComputePassEncoder::argumentTable()
	{
		if (!m_argumentTable && m_encoder)
		{
			m_argumentTable = createArgumentTable(m_device);
		}

		return m_argumentTable.get();
	}

} // namespace lys::mtl
