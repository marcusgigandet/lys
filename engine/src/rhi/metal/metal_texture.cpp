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
export module lys:metal_texture.impl;

import :error;
import :metal_texture;
import :metal_types;
import :rhi_texture;
import std;

namespace lys::mtl
{
	Texture::Texture(MTL::Device& device, MTL4::CommandQueue& queue, const rhi::TextureDesc& desc) :
		Object(device), rhi::Texture(desc), m_commandQueue(queue)
	{
		createTexture();
	}

	Result<void>
	Texture::upload(const std::span<const std::byte> data, const std::size_t bytesPerRow) noexcept
	{
		if (data.empty())
		{
			return makeUnexpected(ErrorCode::InvalidArgument);
		}

		const MTL::Region region{
			0,
			0,
			0,
			m_width,
			m_height,
			1,
		};

		m_texture->replaceRegion(region, 0, data.data(), bytesPerRow);
		return {};
	}

	void Texture::createTexture()
	{
		const auto mtlTexDesc{MTL::TextureDescriptor::texture2DDescriptor(
			toMetalEnum(m_pixelFormat),
			m_width,
			m_height,
			m_mipLevels > 1)};
		mtlTexDesc->setUsage(MTL::TextureUsageShaderRead | MTL::TextureUsageShaderWrite);
		mtlTexDesc->setMipmapLevelCount(m_mipLevels);
		m_texture = NS::TransferPtr(m_device.newTexture(mtlTexDesc));

		// Generate mipmaps
		if (m_mipLevels > 1)
		{
			// blitEncoder->generateMipmaps(m_texture.get());
		}
	}
} // namespace lys::mtl
