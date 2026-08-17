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
export module lys:metal_command_buffer;

import :metal_compute_pass_encoder;
import :metal_object;
import :metal_render_pass_encoder;
import :rhi_command_buffer;
import std;

namespace lys::mtl
{
	export class CommandBuffer final : public Object, public rhi::CommandBuffer
	{
		MTL4::CommandQueue&					  m_commandQueue;
		NS::SharedPtr<MTL4::CommandBuffer>	  m_commandBuffer;
		NS::SharedPtr<MTL4::CommandAllocator> m_commandAllocator;
		std::unique_ptr<ComputePassEncoder>	  m_computePassEncoder;
		std::unique_ptr<RenderPassEncoder>	  m_renderPassEncoder;

	public:
		explicit CommandBuffer(MTL::Device& device, MTL4::CommandQueue& commandQueue);

		[[nodiscard]] MTL4::CommandBuffer* commandBuffer() const noexcept
		{
			return m_commandBuffer.get();
		}

		void begin() override;
		void end() override;

		[[nodiscard]] rhi::ComputePassEncoder& beginComputePass() override;
		[[nodiscard]] rhi::RenderPassEncoder&
		beginRenderPass(const rhi::RenderPassDesc& desc) override;

		void generateMipmaps(const rhi::Texture& texture) override;

	private:
		void endActivePass();
	};
} // namespace lys::mtl
