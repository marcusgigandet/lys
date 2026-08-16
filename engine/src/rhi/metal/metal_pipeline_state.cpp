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
export module lys:metal_pipeline_state.impl;

import :metal_pipeline_state;
import :metal_shader;
import :metal_types;
import :rhi_pipeline_state;
import std;

namespace lys::mtl
{
	RenderPipelineState::RenderPipelineState(
		MTL::Device& device, const rhi::RenderPipelineDesc& desc) :
		Object(device), rhi::RenderPipelineState(desc)
	{
		createRenderPipelineState();
		createDepthStencilState();
	}

	void RenderPipelineState::createRenderPipelineState()
	{
		const auto pipelineDesc{NS::TransferPtr(MTL::RenderPipelineDescriptor::alloc()->init())};

		if (m_desc.vertexShader)
		{
			const auto fn{static_cast<const Shader&>(*m_desc.vertexShader)
							  .function(m_desc.vertexShader->entryPoint())};
			pipelineDesc->setVertexFunction(fn);
		}

		if (m_desc.fragmentShader)
		{
			const auto fn{static_cast<const Shader&>(*m_desc.fragmentShader)
							  .function(m_desc.fragmentShader->entryPoint())};
			pipelineDesc->setFragmentFunction(fn);
		}

		pipelineDesc->colorAttachments()->object(0)->setPixelFormat(
			toMetalEnum(m_desc.colorPixelFormat));

		NS::Error* error{};
		m_renderPipelineState =
			NS::TransferPtr(m_device.newRenderPipelineState(pipelineDesc.get(), &error));

		if (!m_renderPipelineState)
		{
			SPDLOG_ERROR(
				"Failed to create Metal render pipeline state: {}",
				error ? error->description()->cString(NS::UTF8StringEncoding) : "unknown error");
		}
	}

	void RenderPipelineState::createDepthStencilState()
	{
		const auto depthStencilDesc{NS::TransferPtr(MTL::DepthStencilDescriptor::alloc()->init())};

		depthStencilDesc->setDepthWriteEnabled(m_desc.depthWriteEnabled);
		depthStencilDesc->setDepthCompareFunction(toMetalEnum(m_desc.depthCompareFunction));

		m_depthStencilState =
			NS::TransferPtr(m_device.newDepthStencilState(depthStencilDesc.get()));
	}

	ComputePipelineState::ComputePipelineState(
		MTL::Device& device, const rhi::ComputePipelineDesc& desc) :
		Object(device), rhi::ComputePipelineState(desc)
	{
	}
} // namespace lys::mtl
