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
#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION

#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>
export module lys:metal_device;

import :rhi_device;
import std;

namespace lys::mtl
{
	export class Device final : public rhi::Device
	{
		NS::SharedPtr<MTL::Device> m_device;

	public:
		explicit Device(const rhi::DeviceDesc& desc);

		[[nodiscard]] MTL::Device* device() const noexcept { return m_device.get(); }

		[[nodiscard]] std::unique_ptr<rhi::CommandQueue>
		createCommandQueue(rhi::CommandQueueType type) override;

		[[nodiscard]] std::unique_ptr<rhi::Buffer>
		createBuffer(const rhi::BufferDesc& desc) override;

		[[nodiscard]] std::unique_ptr<rhi::Texture>
		createTexture(const rhi::TextureDesc& desc) override;

		[[nodiscard]] std::unique_ptr<rhi::Shader>
		createShader(const rhi::ShaderDesc& desc) override;

		[[nodiscard]] std::unique_ptr<rhi::GraphicsPipelineState>
		createGraphicsPipeline(const rhi::GraphicsPipelineDesc& desc) override;

		[[nodiscard]] std::unique_ptr<rhi::ComputePipelineState>
		createComputePipeline(const rhi::ComputePipelineDesc& desc) override;
	};
} // namespace lys::mtl
