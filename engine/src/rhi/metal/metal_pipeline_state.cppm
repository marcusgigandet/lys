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
export module lys:metal_pipeline_state;

import :rhi_pipeline_state;
import :metal_object;
import std;

namespace lys::mtl
{
	export class RenderPipelineState final : public Object, public rhi::RenderPipelineState
	{
		NS::SharedPtr<MTL::RenderPipelineState>	  m_renderPipelineState;
		NS::SharedPtr<MTL4::RenderCommandEncoder> m_commandEncoder;
		NS::SharedPtr<MTL::DepthStencilState>	  m_depthStencilState;

	public:
		explicit RenderPipelineState(MTL::Device& device, const rhi::RenderPipelineDesc& desc);

		[[nodiscard]] MTL::RenderPipelineState* renderPipelineState() const noexcept
		{
			return m_renderPipelineState.get();
		}

		[[nodiscard]] MTL4::RenderCommandEncoder* renderCommandEncoder() const noexcept
		{
			return m_commandEncoder.get();
		}

		[[nodiscard]] MTL::DepthStencilState* depthStencilState() const noexcept
		{
			return m_depthStencilState.get();
		}

	private:
		void configureEncoder() const;

		void setDepthStencilState();
	};

	export class ComputePipelineState final : public Object, public rhi::ComputePipelineState
	{
		NS::SharedPtr<MTL::ComputePipelineState>   m_computePipelineState;
		NS::SharedPtr<MTL4::ComputeCommandEncoder> m_commandEncoder;

	public:
		explicit ComputePipelineState(MTL::Device& device, const rhi::ComputePipelineDesc& desc);

		[[nodiscard]] MTL::ComputePipelineState* computePipelineState() const noexcept
		{
			return m_computePipelineState.get();
		}

		[[nodiscard]] MTL4::ComputeCommandEncoder* computeCommandEncoder() const noexcept
		{
			return m_commandEncoder.get();
		}
	};
} // namespace lys::mtl
