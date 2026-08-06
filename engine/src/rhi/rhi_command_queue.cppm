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

export module lys:command_queue;

import :command_buffer;
import std;

namespace lys
{
	/**
	 * @brief Types of command queues supported by the RHI.
	 */
	export enum class CommandQueueType
	{
		Graphics,
		Compute,
		Transfer
	};

	export class CommandQueue
	{
		CommandQueueType m_type;

	public:
		explicit CommandQueue(const CommandQueueType type) : m_type(type) {}

		CommandQueue(const CommandQueue&)			 = delete;
		CommandQueue& operator=(const CommandQueue&) = delete;
		CommandQueue(CommandQueue&&)				 = default;
		CommandQueue& operator=(CommandQueue&&)		 = default;

		virtual ~CommandQueue() = default;

	protected:
		virtual void submitImpl(std::span<CommandBuffer* const> commandBuffers) = 0;

		virtual void waitIdleImpl() = 0;
	};
} // namespace lys
