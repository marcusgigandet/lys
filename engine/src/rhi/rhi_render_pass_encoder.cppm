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

export module lys:rhi_render_pass_encoder;

import :rhi_buffer;
import :rhi_pipeline_state;
import :rhi_texture;
import :rhi_types;
import mag;
import std;

namespace lys::rhi
{
	export struct DepthAttachmentDesc
	{
		LoadAction loadAction{LoadAction::Clear};
	};

	export struct RenderPassDesc
	{
		const Texture*					   colorAttachment{nullptr};
		Vec4f							   clearColor{0.05f, 0.05f, 0.05f, 1.0f};
		LoadAction						   loadAction{LoadAction::Clear};
		std::optional<DepthAttachmentDesc> depthAttachmentDesc{std::nullopt};
	};

	export struct DrawDesc
	{
		std::uint32_t vertexCount{0};
		std::uint32_t instanceCount{1};
		std::uint32_t firstVertex{0};
		std::uint32_t firstInstance{0};
	};

	export class RenderPassEncoder
	{
	public:
		RenderPassEncoder()			 = default;
		virtual ~RenderPassEncoder() = default;

		RenderPassEncoder(const RenderPassEncoder&)			   = delete;
		RenderPassEncoder& operator=(const RenderPassEncoder&) = delete;
		RenderPassEncoder(RenderPassEncoder&&)				   = delete;
		RenderPassEncoder& operator=(RenderPassEncoder&&)	   = delete;

		virtual void setPipeline(const RenderPipelineState& state) = 0;

		virtual RenderPassEncoder&
		setResource(ShaderStage stage, const Buffer& buffer, const std::string& name) = 0;
		virtual RenderPassEncoder&
		setResource(ShaderStage stage, const Texture& texture, const std::string& name) = 0;
		virtual RenderPassEncoder&
		setResource(ShaderStage stage, const Buffer& buffer, std::uint32_t index) = 0;
		virtual RenderPassEncoder&
		setResource(ShaderStage stage, const Texture& texture, std::uint32_t index) = 0;

		virtual void draw(PrimitiveType primitiveType, const DrawDesc& desc) = 0;
		virtual void end()													 = 0;
	};
} // namespace lys::rhi
