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
#include <cstddef>
export module lys:rhi_device;

import :command_queue;
import std;

namespace lys
{
	/**
	 * @brief RHI backend options.
	 */
	export enum class RHIBackend
	{
		Auto,	/// Automatically decide which backend to use at runtime
		Vulkan, /// Cross-platform
		Metal,	///< Apple-only
	};

	export struct RHIDeviceConfig
	{
		RHIBackend backend{RHIBackend::Auto};
	};

	export class RHIDevice
	{
		/// Command queue instances
		std::array<std::unique_ptr<CommandQueue>, 3> m_commandQueues{};

	public:
		RHIDevice() = default;
		RHIDevice(const RHIDeviceConfig& config);

		RHIDevice(const RHIDevice&)			   = delete;
		RHIDevice& operator=(const RHIDevice&) = delete;
		RHIDevice(RHIDevice&&)				   = default;
		RHIDevice& operator=(RHIDevice&&)	   = default;
		virtual ~RHIDevice()				   = default;

		[[nodiscard]] CommandQueue& queue(CommandQueueType type);

		[[nodiscard]] CommandQueue& graphicsQueue() { return queue(CommandQueueType::Graphics); }
		[[nodiscard]] CommandQueue& computeQueue() { return queue(CommandQueueType::Compute); }
		[[nodiscard]] CommandQueue& transferQueue() { return queue(CommandQueueType::Transfer); }

	protected:
		/**
		 * @brief Creates a new instance of a CommandQueue.
		 *
		 * @param type Queue type to create.
		 *
		 * @return Ptr to the platform-specific implementation of a CommandQueue.
		 */
		[[nodiscard]] virtual std::unique_ptr<CommandQueue>
		createCommandQueue(CommandQueueType type) = 0;
	};
} // namespace lys
