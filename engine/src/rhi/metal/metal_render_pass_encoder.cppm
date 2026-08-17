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
export module lys:metal_render_pass_encoder;

import :metal_object;
import :rhi_render_pass_encoder;

namespace lys::mtl
{
	export class RenderPassEncoder final : public Object, public rhi::RenderPassEncoder
	{
		NS::SharedPtr<MTL4::RenderCommandEncoder> m_encoder;
		NS::SharedPtr<MTL4::ArgumentTable>		  m_argumentTable;

	public:
		RenderPassEncoder(MTL::Device& device, MTL4::RenderCommandEncoder* encoder);

		void setPipeline(const rhi::RenderPipelineState& state) override;

		RenderPassEncoder& setResource(
			rhi::ShaderStage stage, const rhi::Buffer& buffer, const std::string& name) override;
		RenderPassEncoder& setResource(
			rhi::ShaderStage stage, const rhi::Texture& texture, const std::string& name) override;
		RenderPassEncoder& setResource(
			rhi::ShaderStage stage, const rhi::Buffer& buffer, std::uint32_t index) override;
		RenderPassEncoder& setResource(
			rhi::ShaderStage stage, const rhi::Texture& texture, std::uint32_t index) override;

		void draw(rhi::PrimitiveType primitiveType, const rhi::DrawDesc& desc) override;
		void end() override;

	private:
		MTL4::ArgumentTable* argumentTable();
		void				 bindArgumentTable(rhi::ShaderStage stage) const;
	};
} // namespace lys::mtl
