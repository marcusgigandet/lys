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
export module lys:metal_command_queue;

import :metal_command_buffer;
import :rhi_command_queue;
import :metal_object;
import std;

namespace lys::mtl
{
	export class CommandQueue final : public Object, public rhi::CommandQueue
	{
		NS::SharedPtr<MTL4::CommandQueue> m_commandQueue;
		NS::SharedPtr<MTL::SharedEvent>	  m_idleEvent;
		uint64_t						  m_idleCounter{0};

	public:
		explicit CommandQueue(MTL::Device& device, rhi::CommandQueueType type);

		/**
		 * @brief Returns the native backend CommandQueue.
		 * @return Native metal CommandQueue.
		 */
		[[nodiscard]] MTL4::CommandQueue* commandQueue() const noexcept
		{
			return m_commandQueue.get();
		}

		void submit(std::span<rhi::CommandBuffer* const> commandBuffers) override;

		void wait() override;
	};
} // namespace lys::mtl
