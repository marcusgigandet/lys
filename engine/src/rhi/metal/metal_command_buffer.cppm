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

import :rhi_command_buffer;
import :metal_object;
import :metal_texture;

namespace lys::mtl
{
	export class CommandBuffer final : public Object, public rhi::CommandBuffer
	{
		MTL4::CommandQueue&						   m_commandQueue;
		NS::SharedPtr<MTL4::CommandBuffer>		   m_commandBuffer;
		NS::SharedPtr<MTL4::CommandAllocator>	   m_commandAllocator;
		NS::SharedPtr<MTL4::ComputeCommandEncoder> m_computeCommandEncoder;
		NS::SharedPtr<MTL4::RenderCommandEncoder>  m_renderCommandEncoder;

	public:
		explicit CommandBuffer(MTL::Device& device, MTL4::CommandQueue& commandQueue);

		[[nodiscard]] MTL4::CommandBuffer* commandBuffer() const noexcept
		{
			return m_commandBuffer.get();
		}

		void begin() override;
		void end() override;

		void beginComputePass() override;
		void beginRenderPass(const rhi::RenderPassDesc& desc) override;

		void setComputePipelineState(const rhi::ComputePipelineState& state) override;
		void setRenderPipelineState(const rhi::RenderPipelineState& state) override;

		void generateMipmaps(const rhi::Texture& texture) override;

		CommandBuffer& setResource(
			rhi::ShaderStage stage, const rhi::Buffer& buffer, const std::string& name) override;

		CommandBuffer& setResource(
			rhi::ShaderStage stage, const rhi::Texture& texture, const std::string& name) override;

		CommandBuffer& setResource(
			rhi::ShaderStage stage, const rhi::Buffer& buffer, std::uint32_t index) override;

		CommandBuffer& setResource(
			rhi::ShaderStage stage, const rhi::Texture& texture, std::uint32_t index) override;

	private:
		MTL4::ArgumentTable* makeArgumentTable() const;
		bool				 isEncoderValid(rhi::ShaderStage stage) const;
	};
} // namespace lys::mtl
