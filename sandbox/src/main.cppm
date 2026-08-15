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

export module lys_sandbox;

import lys;
import std;

using namespace lys;

namespace
{
	class Renderer
	{
		std::unique_ptr<rhi::Device> m_device;
		std::unique_ptr<rhi::Shader> m_vertShader;
		std::unique_ptr<rhi::Shader> m_fragShader;

	public:
		Renderer()
		{
			constexpr rhi::DeviceDesc deviceDesc{
				.backend		   = rhi::Backend::Auto,
				.maxFramesInFlight = 3,
			};
			m_device = rhi::createDevice(deviceDesc);

			m_vertShader = m_device->createShader({
				.stage		= rhi::ShaderStage::Vertex,
				.language	= rhi::ShaderLanguage::Metal,
				.entryPoint = "vertexMain",
				.source		= std::filesystem::path("shaders/generic_shader.metal"),
			});
			m_fragShader = m_device->createShader({
				.stage		= rhi::ShaderStage::Vertex,
				.language	= rhi::ShaderLanguage::Metal,
				.entryPoint = "fragmentMain",
				.source		= std::filesystem::path("shaders/generic_shader.metal"),
			});
			m_vertShader->reload();
			m_fragShader->reload();
		}

		void render() const
		{
			auto&	   graphicsQueue{m_device->graphicsQueue()};
			const auto commandBuffer{m_device->createCommandBuffer()};
			const auto renderPipelineState{m_device->createRenderPipeline({
				.vertexShader	= m_vertShader.get(),
				.fragmentShader = m_fragShader.get(),
			})};

			commandBuffer->begin();
			commandBuffer->setRenderPipelineState(*renderPipelineState);
			commandBuffer->end();

			graphicsQueue.submit(*commandBuffer);
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
			m_window = std::make_unique<Window>(windowDesc);

			registerCallbacks();
		}

		void shutdown()
		{
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
		Application app;

		app.run();

		return 0;
	}
}
