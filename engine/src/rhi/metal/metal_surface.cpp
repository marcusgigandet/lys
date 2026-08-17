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
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3native.h>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>
module lys:metal_surface.impl;

import :metal_objc_interop;
import :metal_surface;
import :metal_types;

namespace lys::mtl
{
	void Surface::attachToWindow(const Window& window)
	{
		const auto nsWindow{glfwGetCocoaWindow(window.nativeHandle())};

		createLayer();
		attachLayer(nsWindow);
	}

	void Surface::createLayer()
	{
		m_layer = NS::RetainPtr(CA::MetalLayer::layer());
		m_layer->setDevice(&m_device);
		m_layer->setFramebufferOnly(true);
	}

	void Surface::attachLayer(const id& nsWindow) const
	{
		const auto nsView{objcCall<id>(nsWindow, "contentView")};
		objcCall<void>(nsView, "setWantsLayer:", YES);
		objcCall<void>(nsView, "setLayer:", m_layer.get());
	}
} // namespace lys::mtl
