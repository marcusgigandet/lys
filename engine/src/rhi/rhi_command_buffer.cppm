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

export module lys:rhi_command_buffer;

import std;

namespace lys::rhi
{
	// Forward-declare class
	export class CommandQueue;

	export class CommandBuffer
	{
	public:
		CommandBuffer()			 = default;
		virtual ~CommandBuffer() = default;

		CommandBuffer(const CommandBuffer&)			   = delete;
		CommandBuffer& operator=(const CommandBuffer&) = delete;
		CommandBuffer(CommandBuffer&&)				   = default;
		CommandBuffer& operator=(CommandBuffer&&)	   = default;
	};
} // namespace lys::rhi
