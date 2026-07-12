/*
 * Copyright 2026 Marcus Gigandet
 *
 * All rights reserved.
 */

import lys;
import lum;
import std;

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


	return 0;
}
