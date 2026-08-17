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
#include <spdlog/spdlog.h>
export module lys_sandbox;

import lys;
import std;

using namespace lys;

namespace
{
	struct Vertex
	{
		[[maybe_unused]] Vec3f position;
		[[maybe_unused]] Vec3f color;
	};

	const std::vector<Vertex> vertices{
		{.position = {-0.5f, -0.5f, 0.0f}, .color = {1.0f, 0.0f, 0.0f}},
		{.position = {0.5f, -0.5f, 0.0f}, .color = {0.0f, 1.0f, 0.0f}},
		{.position = {0.0f, 0.5f, 0.0f}, .color = {0.0f, 0.0f, 1.0f}},
	};


	class Renderer
	{
		std::unique_ptr<rhi::Device>			  m_device;
		std::unique_ptr<rhi::Shader>			  m_vertShader;
		std::unique_ptr<rhi::Shader>			  m_fragShader;
		std::unique_ptr<rhi::RenderPipelineState> m_renderPipelineState;
		std::unique_ptr<rhi::Buffer>			  m_vertexBuffer;
		std::unique_ptr<rhi::Surface>			  m_surface;
		std::unique_ptr<rhi::Swapchain>			  m_swapchain;
		Window&									  m_window;

	public:
		explicit Renderer(Window& window) : m_window(window)
		{
			constexpr rhi::DeviceDesc deviceDesc{
				.backend		   = rhi::Backend::Auto,
				.maxFramesInFlight = 3,
			};
			m_device = rhi::createDevice(deviceDesc);

			m_vertShader		  = m_device->createShader({
				.stage		= rhi::ShaderStage::Vertex,
				.language	= rhi::ShaderLanguage::Metal,
				.entryPoint = "vertexMain",
				.source		= std::filesystem::path("shaders/triangle.metal"),
			});
			m_fragShader		  = m_device->createShader({
				.stage		= rhi::ShaderStage::Fragment,
				.language	= rhi::ShaderLanguage::Metal,
				.entryPoint = "fragmentMain",
				.source		= std::filesystem::path("shaders/triangle.metal"),
			});
			m_renderPipelineState = m_device->createRenderPipeline({
				.vertexShader	   = m_vertShader.get(),
				.fragmentShader	   = m_fragShader.get(),
				.depthTestEnabled  = false,
				.depthWriteEnabled = false,
			});
			m_vertexBuffer		  = m_device->createBuffer({
				.size		 = sizeof(Vertex) * vertices.size(),
				.usage		 = rhi::BufferUsage::Vertex,
				.memoryUsage = rhi::MemoryUsage::Shared,
			});
			m_vertexBuffer->upload(vertices.data(), sizeof(Vertex) * vertices.size(), 0);

			m_surface = m_device->createSurface(m_window);

			constexpr rhi::SwapchainDesc swapChainDesc{
				.width		 = 1,
				.height		 = 1,
				.imageCount	 = 3,
				.pixelFormat = rhi::PixelFormat::BGRA8_sRGB,
				.vsync		 = true,
			};
			m_swapchain = m_device->createSwapchain(*m_surface, swapChainDesc);
		}

		~Renderer() = default;

		void renderPass(rhi::CommandBuffer& commandBuffer) const
		{
			const rhi::RenderPassDesc renderPassDesc{
				.colorAttachment = m_swapchain->currentTexture(),
				.clearColor		 = {1.0f, 0.0f, 0.0f, 1.0f},
				.loadAction		 = rhi::LoadAction::Clear,
			};
			auto& passEncoder{commandBuffer.beginRenderPass(renderPassDesc)};
			passEncoder.setPipeline(*m_renderPipelineState);
			passEncoder.setResource(rhi::ShaderStage::Vertex, *m_vertexBuffer, 0);
			passEncoder.draw(
				rhi::PrimitiveType::Triangle,
				{.vertexCount = static_cast<std::uint32_t>(vertices.size())});
			passEncoder.end();
		}

		void render() const
		{
			// Update the swapchain
			const Vec2i size{m_window.framebufferDimensions()};
			m_swapchain->resize(size.x, size.y);
			m_swapchain->acquireNextImage();
			if (!m_swapchain->currentTexture())
			{
				return;
			}

			static auto& graphicsQueue{m_device->renderQueue()};
			const auto	 commandBuffer{m_device->createCommandBuffer()};
			commandBuffer->begin();
			renderPass(*commandBuffer);
			commandBuffer->end();

			graphicsQueue.submit(*commandBuffer);

			// Present the swapchain after processing rendering
			m_swapchain->present();
		}
	};

	class Application
	{
		std::unique_ptr<Window>	  m_window;
		std::unique_ptr<Renderer> m_renderer;

	public:
		~Application() { shutdown(); }

		void run()
		{
			init();

			m_window->show();

			while (!m_window->shouldClose())
			{
				Window::pollEvents();

				m_renderer->render();

				m_window->update();
			}
		}

	private:
		void init()
		{
			const WindowDesc windowDesc{
				.title		= "Lys Sandbox",
				.dimensions = {100, 100},
				.state		= WindowState::Windowed,
				.resizable	= true,
				.visible	= true,
				.vsync		= true,
			};
			m_window   = std::make_unique<Window>(windowDesc);
			m_renderer = std::make_unique<Renderer>(*m_window);

			registerCallbacks();
		}

		void shutdown()
		{
			m_renderer.reset();
			m_window.reset();
			Window::terminate();
		}

		void registerCallbacks() const
		{
			m_window->inputManager().addKeyEventListener(
				[this](const KeyInputEvent& event)
				{
					if (event.key == KEY_ESCAPE && event.action == InputEdge::Press)
					{
						m_window->close();
					}
				});
		}
	};
} // namespace

extern "C++"
{
	int main()
	{
		// Configure spdlog
		spdlog::set_pattern("[%H:%M:%S.%e] [%^%l%$] [%s:%#] %v");
		spdlog::set_level(spdlog::level::trace);

		// Run the app
		Application app;
		app.run();

		return 0;
	}
}
