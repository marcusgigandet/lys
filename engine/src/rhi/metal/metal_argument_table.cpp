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
#include <spdlog/spdlog.h>
module lys:metal_argument_table.impl;

import :metal_argument_table;

namespace lys::mtl
{
	NS::SharedPtr<MTL4::ArgumentTable> createArgumentTable(MTL::Device& device)
	{
		const auto descriptor{NS::TransferPtr(MTL4::ArgumentTableDescriptor::alloc()->init())};
		descriptor->setMaxBufferBindCount(31);
		descriptor->setMaxTextureBindCount(31);
		descriptor->setMaxSamplerStateBindCount(16);
		descriptor->setInitializeBindings(true);

		NS::Error* nsError{};
		auto	   table{NS::TransferPtr(device.newArgumentTable(descriptor.get(), &nsError))};
		if (nsError)
		{
			SPDLOG_ERROR(
				"Failed to create Metal argument table: {}",
				nsError->description()->cString(NS::UTF8StringEncoding));
			return {};
		}

		return table;
	}
} // namespace lys::mtl
