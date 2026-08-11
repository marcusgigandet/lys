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
#include <cstdint>
export module lys:rhi_types;

namespace lys::rhi
{
	export enum class PixelFormat : std::uint8_t
	{
		Undefined = 0u,

		R8_UNorm,
		RG8_UNorm,
		RGBA8_UNorm,
		RGBA8_sRGB,

		BGRA8_UNorm,
		BGRA8_sRGB,

		R16_Float,
		RG16_Float,
		RGBA16_Float,

		R32_Float,
		RG32_Float,
		RGBA32_Float,
	};


	export enum class DepthFormat : std::uint8_t
	{
		Undefined = 0u,
		Depth16_UNorm,
		Depth32_Float,
	};


	export enum class StencilFormat : std::uint8_t
	{
		Undefined = 0u,
		Stencil8_UNorm,
	};


	export enum class PrimitiveType : std::uint8_t
	{
		Point = 0u,
		Line,
		LineStrip,
		Triangle,
		TriangleStrip,
	};


	export enum class FillMode : std::uint8_t
	{
		Fill = 0u,
		Line
	};


	export enum class CullMode : std::uint8_t
	{
		None = 0,
		Front,
		Back
	};


	export enum class Winding : std::uint8_t
	{
		Clockwise = 0u,
		CounterClockwise
	};


	/**
	 * @brief Compare functions supported by RHI.
	 *
	 * Used during rendering draws.
	 */
	export enum class CompareFunction : std::uint8_t
	{
		Less = 0u,
		LessEqual,
		Equal,
		NotEqual,
		Greater,
		GreaterEqual,
		Always,
		Never,
	};


	/**
	 * @brief Memory management of GPU resources.
	 *
	 * Sets the accessibility and method of memory usage for the GPU resource.
	 */
	export enum class MemoryUsage
	{
		Private = 0u, ///< GPU local memory
		Managed,	  ///< Both the GPU and CPU maintain separate copies of the data
		Shared,		  ///< Both CPU and GPU can read and write
	};


	export [[nodiscard]] constexpr uint8_t channelCount(const PixelFormat format) noexcept
	{
		using PF = PixelFormat;

		switch (format)
		{
		case PF::R8_UNorm:
		case PF::R16_Float:
		case PF::R32_Float:
			return 1;

		case PF::RG8_UNorm:
		case PF::RG16_Float:
		case PF::RG32_Float:
			return 2;

		case PF::RGBA8_UNorm:
		case PF::RGBA8_sRGB:
		case PF::RGBA16_Float:
		case PF::RGBA32_Float:
		case PF::BGRA8_UNorm:
		case PF::BGRA8_sRGB:
			return 4;

		case PF::Undefined:
		default:
			return 0;
		}
	}
} // namespace lys::rhi
