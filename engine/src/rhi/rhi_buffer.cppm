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

export module lys:rhi_buffer;

import :error;
import :rhi_types;
import std;

namespace lys::rhi
{
	export enum class BufferUsage
	{
		Vertex,
		Index,
		Uniform,
		Storage,
		Staging,
	};

	export struct BufferDesc
	{
		std::size_t size{0};
		BufferUsage usage{BufferUsage::Staging};
		MemoryUsage memoryUsage{MemoryUsage::Private};
	};

	export class Buffer
	{
	protected:
		std::size_t m_size;
		BufferUsage m_usage;
		MemoryUsage m_memoryUsage;

	public:
		explicit Buffer(const BufferDesc& desc);
		virtual ~Buffer() = default;

		Buffer(const Buffer&)			 = delete;
		Buffer& operator=(const Buffer&) = delete;
		Buffer(Buffer&&)				 = default;
		Buffer& operator=(Buffer&&)		 = default;

		virtual Result<void>
		upload(const void* pData, std::uint32_t size, std::uint32_t offset) = 0;

		virtual std::span<const std::byte> data() const = 0;

		[[nodiscard]] std::size_t size() const noexcept { return m_size; }
		[[nodiscard]] BufferUsage usage() const noexcept { return m_usage; }
		[[nodiscard]] MemoryUsage memoryUsage() const noexcept { return m_memoryUsage; }
	};
} // namespace lys::rhi
