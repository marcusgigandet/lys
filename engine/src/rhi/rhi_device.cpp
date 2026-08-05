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
module lys:rhi_device.impl;

import :rhi_device;
import std;

namespace lys
{
	CommandQueue& RHIDevice::queue(const CommandQueueType type)
	{
		const auto index{static_cast<size_t>(type)};
		auto&	   queue{m_commandQueues[index]};

		// Check if the queue is null
		if (!queue)
		{
			// Creat a new queue instance
			queue = createCommandQueue(type);
		}

		return *queue;
	}
} // namespace lys
