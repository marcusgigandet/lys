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

export module lys:rhi_swapchain;

import :rhi_surface;
import :rhi_texture;
import :rhi_types;
import std;

namespace lys::rhi
{
	export struct SwapchainDesc
	{
		std::uint32_t width{1};
		std::uint32_t height{1};
		std::uint8_t  imageCount{3};
		PixelFormat	  pixelFormat{PixelFormat::BGRA8_sRGB};
		bool		  vsync{true};
	};

	export class Swapchain
	{
	protected:
		Surface&	  m_surface;
		SwapchainDesc m_desc;

	public:
		explicit Swapchain(Surface& surface, const SwapchainDesc& desc) :
			m_surface(surface), m_desc(desc)
		{
		}
		virtual ~Swapchain() = default;

		Swapchain(const Swapchain&)			   = delete;
		Swapchain& operator=(const Swapchain&) = delete;
		Swapchain(Swapchain&&)				   = delete;
		Swapchain& operator=(Swapchain&&)	   = delete;

		virtual void						 resize(std::uint32_t width, std::uint32_t height) = 0;
		virtual void						 acquireNextImage()								   = 0;
		virtual void						 present()										   = 0;
		[[nodiscard]] virtual const Texture* currentTexture() const noexcept				   = 0;

		[[nodiscard]] const SwapchainDesc& desc() const noexcept { return m_desc; }
		[[nodiscard]] Surface&			   surface() noexcept { return m_surface; }
		[[nodiscard]] const Surface&	   surface() const noexcept { return m_surface; }
	};
} // namespace lys::rhi
