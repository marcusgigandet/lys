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
#include <QuartzCore/CAMetalLayer.hpp>
#include <objc/objc.h>
export module lys:metal_surface;

import :metal_object;
import :rhi_surface;
import :window;

namespace lys::mtl
{
	export class Surface : public Object, public rhi::Surface
	{
		NS::SharedPtr<CA::MetalLayer> m_layer;

	public:
		explicit Surface(MTL::Device& device, const Window& window) :
			Object(device), rhi::Surface(window)
		{
			attachToWindow(m_window);
		}

		~Surface() override = default;

		[[nodiscard]] CA::MetalLayer* layer() const noexcept { return m_layer.get(); }

		void attachToWindow(const Window& window);

	private:
		void createLayer();
		void attachLayer(const id& nsWindow) const;
	};
} // namespace lys::mtl
