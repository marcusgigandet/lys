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
		Window						 m_window;
		std::unique_ptr<rhi::Device> m_device;

	public:
		void run()
		{
			init();

			m_window.show();

			while (!m_window.shouldClose())
			{
				m_window.update();

				Window::pollEvents();
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
			m_window = Window(windowDesc);
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
