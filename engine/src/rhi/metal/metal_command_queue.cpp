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
export module lys:metal_command_queue.impl;

import :metal_command_queue;
import :metal_command_buffer;
import std;

namespace lys::mtl
{
	CommandQueue::CommandQueue(MTL::Device& device, const rhi::CommandQueueType type) :
		rhi::CommandQueue(type), m_device(device)
	{
		m_commandQueue = NS::TransferPtr(m_device.newMTL4CommandQueue());
		m_idleEvent	   = NS::TransferPtr(m_device.newSharedEvent());
	}

	void CommandQueue::submit(const std::span<rhi::CommandBuffer* const> commandBuffers)
	{
		std::vector<const MTL4::CommandBuffer*> metalBuffers;
		metalBuffers.reserve(commandBuffers.size());

		for (auto* buf : commandBuffers)
		{
			metalBuffers.push_back(static_cast<CommandBuffer*>(buf)->commandBuffer());
		}

		m_commandQueue->commit(metalBuffers.data(), metalBuffers.size());
	}

	void CommandQueue::wait()
	{
		m_commandQueue->signalEvent(m_idleEvent.get(), ++m_idleCounter);
		m_idleEvent->waitUntilSignaledValue(m_idleCounter, UINT64_MAX);
	}
} // namespace lys::mtl
