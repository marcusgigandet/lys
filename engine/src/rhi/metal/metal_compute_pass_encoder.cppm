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
export module lys:metal_compute_pass_encoder;

import :metal_object;
import :rhi_compute_pass_encoder;

namespace lys::mtl
{
	export class ComputePassEncoder final : public Object, public rhi::ComputePassEncoder
	{
		NS::SharedPtr<MTL4::ComputeCommandEncoder> m_encoder;
		NS::SharedPtr<MTL4::ArgumentTable>		   m_argumentTable;

	public:
		ComputePassEncoder(MTL::Device& device, MTL4::ComputeCommandEncoder* encoder);

		void setPipeline(const rhi::ComputePipelineState& state) override;

		ComputePassEncoder&
		setResource(const rhi::Buffer& buffer, const std::string& name) override;
		ComputePassEncoder&
		setResource(const rhi::Texture& texture, const std::string& name) override;
		ComputePassEncoder& setResource(const rhi::Buffer& buffer, std::uint32_t index) override;
		ComputePassEncoder& setResource(const rhi::Texture& texture, std::uint32_t index) override;

		void dispatch(const rhi::DispatchDesc& desc) override;
		void end() override;

	private:
		MTL4::ArgumentTable* argumentTable();
	};
} // namespace lys::mtl
