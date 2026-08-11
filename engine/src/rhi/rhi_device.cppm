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

export module lys:rhi_device;

import :rhi_buffer;
import :rhi_command_queue;
import :rhi_error;
import :rhi_pipeline_state;
import :rhi_shader;
import :rhi_texture;
import std;

namespace lys::rhi
{
	/**
	 * @brief RHI backend options.
	 */
	export enum class Backend : std::uint8_t
	{
		Auto,	///< Automatically decide which backend to use at runtime
		Vulkan, ///< Cross-platform
		Metal,	///< Apple-only
	};

	export struct DeviceDesc
	{
		Backend		 backend{Backend::Auto};
		std::uint8_t maxFramesInFlight{3};
	};

	export class Device
	{
		DeviceDesc m_desc;

		/// Command queue instances
		std::array<std::unique_ptr<CommandQueue>, 3> m_commandQueues{};

	public:
		explicit Device(const DeviceDesc& desc = {});

		Device(const Device&)			 = delete;
		Device& operator=(const Device&) = delete;
		Device(Device&&)				 = default;
		Device& operator=(Device&&)		 = default;

		virtual ~Device() = default;

		[[nodiscard]] CommandQueue& queue(CommandQueueType type);

		[[nodiscard]] CommandQueue& graphicsQueue() { return queue(CommandQueueType::Graphics); }
		[[nodiscard]] CommandQueue& computeQueue() { return queue(CommandQueueType::Compute); }
		[[nodiscard]] CommandQueue& transferQueue() { return queue(CommandQueueType::Transfer); }

		/**
		 * @brief Creates a new instance of a CommandQueue.
		 *
		 * @param type Queue type to create.
		 *
		 * @return Ptr to the platform-specific implementation of a CommandQueue.
		 */
		[[nodiscard]] virtual std::unique_ptr<CommandQueue>
		createCommandQueue(CommandQueueType type) = 0;

		[[nodiscard]] virtual std::unique_ptr<Buffer> createBuffer(const BufferDesc& desc) = 0;

		[[nodiscard]] virtual std::unique_ptr<Texture> createTexture(const TextureDesc& desc) = 0;

		[[nodiscard]] virtual std::unique_ptr<Shader> createShader(const ShaderDesc& desc) = 0;

		[[nodiscard]] virtual std::unique_ptr<GraphicsPipelineState>
		createGraphicsPipeline(const GraphicsPipelineDesc& desc) = 0;

		[[nodiscard]] virtual std::unique_ptr<ComputePipelineState>
		createComputePipeline(const ComputePipelineDesc& desc) = 0;
	};

	export [[nodiscard]] std::unique_ptr<Device> createDevice(const DeviceDesc& desc);
} // namespace lys::rhi
