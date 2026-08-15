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
#include <array>
#include <spdlog/spdlog.h>
export module lys:metal_types;

import :rhi_types;

namespace lys::mtl
{
	template <typename Enum, typename T, std::size_t N>
	[[nodiscard]] constexpr T
	enumLookup(const Enum value, const std::array<T, N>& table, const T fallback) noexcept
	{
		const auto index{static_cast<std::size_t>(value)};
		if (index >= table.size())
		{
			SPDLOG_DEBUG("enumLookup: Invalid index {}, defaulting to fallback", index);
			return fallback;
		}

		return table[index];
	}

	constexpr std::array WindingToMetal{
		MTL::WindingClockwise,
		MTL::WindingCounterClockwise,
	};

	constexpr std::array CompareFunctionToMetal{
		MTL::CompareFunctionLess,
		MTL::CompareFunctionLessEqual,
		MTL::CompareFunctionEqual,
		MTL::CompareFunctionNotEqual,
		MTL::CompareFunctionGreater,
		MTL::CompareFunctionGreaterEqual,
		MTL::CompareFunctionAlways,
		MTL::CompareFunctionNever,
	};

	constexpr std::array FillModeToMetal{
		MTL::TriangleFillModeFill,
		MTL::TriangleFillModeLines,
	};

	constexpr std::array CullModeToMetal{
		MTL::CullModeNone,
		MTL::CullModeFront,
		MTL::CullModeBack,
	};

	constexpr std::array LoadActionToMetal{
		MTL::LoadActionClear,
		MTL::LoadActionLoad,
	};

	constexpr std::array PrimitiveTypeToMetal{
		MTL::PrimitiveTypePoint,
		MTL::PrimitiveTypeLine,
		MTL::PrimitiveTypeLineStrip,
		MTL::PrimitiveTypeTriangle,
		MTL::PrimitiveTypeTriangleStrip,
	};

	constexpr std::array MemoryUsageToMetal{
		MTL::ResourceStorageModePrivate,
		MTL::ResourceStorageModeManaged,
		MTL::ResourceStorageModeShared,
	};

	constexpr std::array PixelFormatToMetal{
		MTL::PixelFormatInvalid,
		MTL::PixelFormatR8Unorm,
		MTL::PixelFormatRG8Unorm,
		MTL::PixelFormatRGBA8Unorm,
		MTL::PixelFormatRGBA8Unorm_sRGB,
		MTL::PixelFormatBGRA8Unorm,
		MTL::PixelFormatBGRA8Unorm_sRGB,
		MTL::PixelFormatR16Float,
		MTL::PixelFormatRG16Float,
		MTL::PixelFormatRGBA16Float,
		MTL::PixelFormatR32Float,
		MTL::PixelFormatRG32Float,
		MTL::PixelFormatRGBA32Float,
	};


	constexpr std::array DepthFormatToMetal{
		MTL::PixelFormatDepth16Unorm,
		MTL::PixelFormatDepth32Float,
	};

	constexpr std::array StencilFormatToMetal{
		MTL::PixelFormatStencil8,
	};

	inline constexpr std::array IndexTypeToMetal{
		MTL::IndexTypeUInt16,
		MTL::IndexTypeUInt32,
	};

	[[nodiscard]] constexpr MTL::Winding toMetalEnum(const rhi::Winding value) noexcept
	{
		return enumLookup(value, WindingToMetal, MTL::WindingCounterClockwise);
	}


	[[nodiscard]] constexpr MTL::CompareFunction
	toMetalEnum(const rhi::CompareFunction value) noexcept
	{
		return enumLookup(value, CompareFunctionToMetal, MTL::CompareFunctionLess);
	}


	[[nodiscard]] constexpr MTL::TriangleFillMode toMetalEnum(const rhi::FillMode value) noexcept
	{
		return enumLookup(value, FillModeToMetal, MTL::TriangleFillModeFill);
	}


	[[nodiscard]] constexpr MTL::CullMode toMetalEnum(const rhi::CullMode value) noexcept
	{
		return enumLookup(value, CullModeToMetal, MTL::CullModeNone);
	}


	[[nodiscard]] constexpr MTL::PrimitiveType toMetalEnum(const rhi::PrimitiveType value) noexcept
	{
		return enumLookup(value, PrimitiveTypeToMetal, MTL::PrimitiveTypeTriangle);
	}


	[[nodiscard]] constexpr MTL::ResourceOptions toMetalEnum(const rhi::MemoryUsage value) noexcept
	{
		return enumLookup(value, MemoryUsageToMetal, MTL::ResourceStorageModePrivate);
	}


	[[nodiscard]] constexpr MTL::PixelFormat toMetalEnum(const rhi::PixelFormat value) noexcept
	{
		return enumLookup(value, PixelFormatToMetal, MTL::PixelFormatInvalid);
	}


	[[nodiscard]] constexpr MTL::PixelFormat toMetalEnum(const rhi::DepthFormat value) noexcept
	{
		return enumLookup(value, DepthFormatToMetal, MTL::PixelFormatInvalid);
	}


	[[nodiscard]] constexpr MTL::PixelFormat toMetalEnum(const rhi::StencilFormat value) noexcept
	{
		return enumLookup(value, StencilFormatToMetal, MTL::PixelFormatInvalid);
	}

	[[nodiscard]] constexpr MTL::LoadAction toMetalEnum(const rhi::LoadAction value) noexcept
	{
		return enumLookup(value, LoadActionToMetal, MTL::LoadActionDontCare);
	}
} // namespace lys::mtl
