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
#include <QuartzCore/CAMetalLayer.hpp>
#include <spdlog/spdlog.h>
export module lys:metal_swapchain.impl;

import :metal_swapchain;
import :metal_types;
import std;

namespace lys::mtl
{
	Swapchain::Swapchain(rhi::Surface& surface, const rhi::SwapchainDesc& desc) :
		rhi::Swapchain(surface, desc)
	{
		configureLayer();
		resize(desc.width, desc.height);
	}

	void Swapchain::resize(const std::uint32_t width, const std::uint32_t height)
	{
		m_desc.width  = width;
		m_desc.height = height;
		const CGSize size{
			static_cast<CGFloat>(width),
			static_cast<CGFloat>(height),
		};

		const auto layer{static_cast<Surface&>(m_surface).layer()};
		if (!layer)
		{
			SPDLOG_WARN("Nullptr layer.");
			return;
		}

		layer->setDrawableSize(size);
	}

	void Swapchain::acquireNextImage()
	{
		const auto layer{static_cast<Surface&>(m_surface).layer()};

		if (!layer)
		{
			SPDLOG_WARN("Nullptr layer.");
			return;
		}

		m_drawable = NS::RetainPtr(layer->nextDrawable());
		if (!m_drawable)
		{
			m_texture.reset();
			return;
		}

		m_texture = std::make_unique<Texture>(
			*m_drawable->texture()->device(),
			*m_drawable->texture(),
			rhi::TextureDesc{
				.width		 = m_desc.width,
				.height		 = m_desc.height,
				.pixelFormat = m_desc.pixelFormat,
			});
	}

	void Swapchain::present()
	{
		if (m_drawable)
		{
			m_drawable->present();
			m_texture.reset();
			m_drawable.reset();
		}
	}

	void Swapchain::configureLayer() const
	{
		const auto layer = static_cast<Surface&>(m_surface).layer();

		if (!layer)
		{
			SPDLOG_WARN("Nullptr layer.");
			return;
		}

		layer->setMaximumDrawableCount(m_desc.imageCount);
		layer->setPixelFormat(toMetalEnum(m_desc.pixelFormat));
		layer->setDisplaySyncEnabled(m_desc.vsync);
	}
} // namespace lys::mtl
