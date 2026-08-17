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

export module lys:rhi_compute_pass_encoder;

import :rhi_buffer;
import :rhi_pipeline_state;
import :rhi_texture;
import mag;
import std;

namespace lys::rhi
{
	export struct DispatchDesc
	{
		Vec3u threadCount{1};
		Vec3u threadsPerGroup{1};
	};

	export class ComputePassEncoder
	{
	public:
		ComputePassEncoder()		  = default;
		virtual ~ComputePassEncoder() = default;

		ComputePassEncoder(const ComputePassEncoder&)			 = delete;
		ComputePassEncoder& operator=(const ComputePassEncoder&) = delete;
		ComputePassEncoder(ComputePassEncoder&&)				 = delete;
		ComputePassEncoder& operator=(ComputePassEncoder&&)		 = delete;

		virtual void setPipeline(const ComputePipelineState& state) = 0;

		virtual ComputePassEncoder& setResource(const Buffer& buffer, const std::string& name) = 0;
		virtual ComputePassEncoder&
		setResource(const Texture& texture, const std::string& name)						 = 0;
		virtual ComputePassEncoder& setResource(const Buffer& buffer, std::uint32_t index)	 = 0;
		virtual ComputePassEncoder& setResource(const Texture& texture, std::uint32_t index) = 0;

		virtual void dispatch(const DispatchDesc& desc) = 0;
		virtual void end()								= 0;
	};
} // namespace lys::rhi
