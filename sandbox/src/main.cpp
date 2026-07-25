/*
 * Copyright 2026 Marcus Gigandet
 *
 * All rights reserved.
 */

export module lys_sandbox;

import lys;
import lum;
import std;

using namespace lum;
using namespace lys;

namespace
{
	class Application
	{
		Window m_window;
		VulkanContext m_vkContext;

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
			const WindowDesc windowDesc{
				.title = "Lys Sandbox",
				.dimensions = {100, 100},
				.state = WindowState::Windowed,
				.resizable = true,
				.visible = true,
				.vsync = true,
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
