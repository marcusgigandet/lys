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
export module lys:metal_buffer.impl;

import :metal_buffer;
import :metal_types;
import :rhi_buffer;
import :rhi_error;

namespace lys::mtl
{
	rhi::Result<void>
	Buffer::upload(const void* pData, const std::uint32_t size, const std::uint32_t offset)
	{
		// Check for nullptr
		if (!pData)
		{
			return rhi::makeUnexpected(rhi::ErrorCode::InvalidArgument);
		}

		switch (m_buffer->storageMode())
		{
		case MTL::StorageModeShared:
			uploadToCPUAccessibleBuffer(pData, size, offset);
			break;
		default:
			return rhi::makeUnexpected(rhi::ErrorCode::NotImplemented);
		}

		return {};
	}

	std::span<const std::byte> Buffer::data() const
	{
		return std::span{
			static_cast<const std::byte*>(m_buffer->contents()),
			m_buffer->allocatedSize(),
		};
	}

	void Buffer::uploadToCPUAccessibleBuffer(
		const void* pData, const std::uint32_t size, const std::uint32_t offset) const
	{
		// Cast buffer to bytes and copy data directly to buffer
		void* dst{static_cast<std::byte*>(m_buffer->contents()) + offset};
		memcpy(dst, pData, size);

		if (m_buffer->storageMode() == MTL::StorageModeManaged)
		{
			// We must inform the GPU that the CPU has modified a section of the buffer
			m_buffer->didModifyRange({offset, size});
		}
	}
} // namespace lys::mtl
