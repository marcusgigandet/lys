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

export module lys:rhi_texture;

import :error;
import :rhi_types;
import std;

namespace lys::rhi
{
	/**
	 * @brief Texture types supported by the RHI.
	 */
	export enum class TextureType
	{
		Texture2D,
	};

	/**
	 * @brief Texture description configuration to use on initialization.
	 */
	export struct TextureDesc
	{
		TextureType	  type{TextureType::Texture2D};
		std::uint32_t width{1};
		std::uint32_t height{1};
		std::uint32_t depthOrLayers{1};
		std::uint32_t mipLevels{1};
		PixelFormat	  pixelFormat{PixelFormat::BGRA8_sRGB};
		DepthFormat	  depthFormat{DepthFormat::Depth32_Float};
	};

	export class Texture
	{
	protected:
		TextureType	  m_type;
		std::uint32_t m_width;
		std::uint32_t m_height;
		std::uint32_t m_depthOrLayers;
		std::uint32_t m_mipLevels;
		PixelFormat	  m_pixelFormat;
		DepthFormat	  m_depthFormat;

	public:
		explicit Texture(const TextureDesc& desc);
		virtual ~Texture() = default;

		Texture(const Texture&)			   = delete;
		Texture& operator=(const Texture&) = delete;
		Texture(Texture&&)				   = default;
		Texture& operator=(Texture&&)	   = default;

		[[nodiscard]] TextureType	type() const noexcept { return m_type; }
		[[nodiscard]] std::uint32_t width() const noexcept { return m_width; }
		[[nodiscard]] std::uint32_t height() const noexcept { return m_height; }
		[[nodiscard]] std::uint32_t depthOrLayers() const noexcept { return m_depthOrLayers; }
		[[nodiscard]] std::uint32_t mipLevels() const noexcept { return m_mipLevels; }
		[[nodiscard]] PixelFormat	pixelFormat() const noexcept { return m_pixelFormat; }
		[[nodiscard]] DepthFormat	depthFormat() const noexcept { return m_depthFormat; }

		virtual Result<void>
		upload(std::span<const std::byte> data, std::size_t bytesPerRow) noexcept = 0;
	};
} // namespace lys::rhi
