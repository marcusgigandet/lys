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
export module lys:metal_buffer;

import :rhi_buffer;
import :error;
import :metal_types;

namespace lys::mtl
{
	export class Buffer final : public rhi::Buffer
	{
		MTL::Device&			   m_device;
		NS::SharedPtr<MTL::Buffer> m_buffer;

	public:
		explicit Buffer(const rhi::BufferDesc& desc, MTL::Device& device) :
			rhi::Buffer(desc), m_device(device)
		{
			m_buffer =
				NS::TransferPtr(m_device.newBuffer(desc.size, toMetalEnum(desc.memoryUsage)));
		}

		Result<void> upload(const void* pData, std::uint32_t size, std::uint32_t offset) override;

		std::span<const std::byte> data() const override;

	private:
		void uploadToCPUAccessibleBuffer(
			const void* pData, std::uint32_t size, std::uint32_t offset) const;
	};
} // namespace lys::mtl
