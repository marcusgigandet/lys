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

export module lys:rhi_pipeline_state;

import :error;
import :rhi_types;
import :rhi_shader;

namespace lys::rhi
{
	export struct RenderPipelineDesc
	{
		const Shader*	vertexShader{nullptr};
		const Shader*	fragmentShader{nullptr};
		PrimitiveType	primitiveType{PrimitiveType::Triangle};
		FillMode		fillMode{FillMode::Fill};
		CullMode		cullMode{CullMode::Back};
		Winding			winding{Winding::CounterClockwise};
		CompareFunction depthCompareFunction{CompareFunction::Less};
		bool			depthTestEnabled{true};
		bool			depthWriteEnabled{true};
	};

	export struct ComputePipelineDesc
	{
		const Shader* computeShader{nullptr};
	};

	export class PipelineState
	{
	public:
		PipelineState()			 = default;
		virtual ~PipelineState() = default;

		PipelineState(const PipelineState&)			   = delete;
		PipelineState& operator=(const PipelineState&) = delete;
		PipelineState(PipelineState&&)				   = default;
		PipelineState& operator=(PipelineState&&)	   = default;
	};

	export class RenderPipelineState : public PipelineState
	{
	protected:
		RenderPipelineDesc m_desc;

	public:
		explicit RenderPipelineState(const RenderPipelineDesc& desc);

		RenderPipelineState(const RenderPipelineState&)			   = delete;
		RenderPipelineState& operator=(const RenderPipelineState&) = delete;
		RenderPipelineState(RenderPipelineState&&)				   = default;
		RenderPipelineState& operator=(RenderPipelineState&&)	   = default;

		[[nodiscard]] const RenderPipelineDesc& desc() const noexcept { return m_desc; }
	};

	export class ComputePipelineState : public PipelineState
	{
	protected:
		ComputePipelineDesc m_desc;

	public:
		explicit ComputePipelineState(const ComputePipelineDesc& desc);

		ComputePipelineState(const ComputePipelineState&)			 = delete;
		ComputePipelineState& operator=(const ComputePipelineState&) = delete;
		ComputePipelineState(ComputePipelineState&&)				 = default;
		ComputePipelineState& operator=(ComputePipelineState&&)		 = default;

		[[nodiscard]] const ComputePipelineDesc& desc() const noexcept { return m_desc; }
	};
} // namespace lys::rhi
