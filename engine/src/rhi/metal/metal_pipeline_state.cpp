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
export module lys:metal_pipeline_state.impl;

import :metal_pipeline_state;
import :metal_types;
import :rhi_pipeline_state;
import std;

namespace lys::mtl
{
	RenderPipelineState::RenderPipelineState(
		MTL::Device& device, const rhi::RenderPipelineDesc& desc) :
		Object(device), rhi::RenderPipelineState(desc)
	{
		configureEncoder();
		setDepthStencilState();
	}

	void RenderPipelineState::configureEncoder() const
	{
		m_commandEncoder->setCullMode(toMetalEnum(m_desc.cullMode));
		m_commandEncoder->setFrontFacingWinding(toMetalEnum(m_desc.winding));
	}

	void RenderPipelineState::setDepthStencilState()
	{
		const auto depthStencilDesc{NS::TransferPtr(MTL::DepthStencilDescriptor::alloc()->init())};

		depthStencilDesc->setDepthWriteEnabled(m_desc.depthWriteEnabled);
		depthStencilDesc->setDepthCompareFunction(toMetalEnum(m_desc.depthCompareFunction));

		m_depthStencilState =
			NS::TransferPtr(m_device.newDepthStencilState(depthStencilDesc.get()));
		m_commandEncoder->setDepthStencilState(m_depthStencilState.get());
	}

	ComputePipelineState::ComputePipelineState(
		MTL::Device& device, const rhi::ComputePipelineDesc& desc) :
		Object(device), rhi::ComputePipelineState(desc)
	{
	}
} // namespace lys::mtl
