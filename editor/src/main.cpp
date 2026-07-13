/*
 * Copyright 2026 Marcus Gigandet
 *
 * All rights reserved.
 */

export module lys.editor;

import lys;
import lum;
import std;

extern "C++"
{
	int main()
	{
		const lys::WindowDesc windowDesc{
			.title = "Lys Editor",
			.dimensions = {100, 100},
			.state = lys::WindowState::Windowed,
			.resizable = true,
			.visible = true,
			.vsync = true,
		};
		lys::Window window{windowDesc};
		window.show();

		while (!window.shouldClose())
		{
			window.update();

			lys::Window::pollEvents();
		}

		return 0;
	}
}
