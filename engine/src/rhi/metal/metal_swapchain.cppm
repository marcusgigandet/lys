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
export module lys:metal_swapchain;

import :metal_surface;
import :rhi_swapchain;
import std;

namespace lys::mtl
{
	export class Swapchain final : public rhi::Swapchain
	{
		NS::SharedPtr<CA::MetalDrawable> m_drawable{};

	public:
		explicit Swapchain(rhi::Surface& surface, const rhi::SwapchainDesc& desc);

		~Swapchain() override = default;

		void resize(std::uint32_t width, std::uint32_t height) override;
		void acquireNextImage() override;
		void present() override;

		[[nodiscard]] CA::MetalDrawable* drawable() const noexcept { return m_drawable.get(); }

	private:
		void configureLayer() const;
	};
} // namespace lys::mtl
