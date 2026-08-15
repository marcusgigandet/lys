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
	class Application
	{
		std::unique_ptr<Window>		 m_window;
		std::unique_ptr<rhi::Device> m_device;

	public:
		~Application() { shutdown(); }

		void run()
		{
			init();

			m_window->show();

			while (!m_window->shouldClose())
			{
				Window::pollEvents();

				render();

				m_window->update();
			}
		}

	private:
		void init()
		{
			m_device = rhi::createDevice({
				.backend = rhi::Backend::Auto,
			});

			const WindowDesc windowDesc{
				.title		= "Lys Sandbox",
				.dimensions = {100, 100},
				.state		= WindowState::Windowed,
				.resizable	= true,
				.visible	= true,
				.vsync		= true,
			};
			m_window = std::make_unique<Window>(windowDesc);

			constexpr rhi::DeviceDesc deviceDesc{
				.backend		   = rhi::Backend::Auto,
				.maxFramesInFlight = 3,
			};
			m_device = createDevice(deviceDesc);

			register_callbacks();
		}

		void shutdown()
		{
			m_window.reset();
			Window::terminate();
		}

		void register_callbacks() const
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

		void render()
		{
			auto& graphicsQueue{m_device->graphicsQueue()};
			auto  commandBuffer{m_device->createCommandBuffer()};
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
