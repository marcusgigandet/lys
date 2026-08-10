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
module lys:metal_device.impl;

import :metal_device;
import std;

namespace lys::mtl
{
	std::unique_ptr<rhi::CommandQueue>
	Device::createCommandQueue([[maybe_unused]] const rhi::CommandQueueType type)
	{
		throw std::runtime_error("Metal command queues are not implemented yet.");
	}
} // namespace lys::mtl
