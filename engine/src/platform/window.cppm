/*
 * Copyright 2026 Marcus Gigandet
 *
 * All rights reserved.
 */

module;
#include <GLFW/glfw3.h>
export module lys:window;

import mag;
import std;

namespace lys
{
	export enum class WindowState
	{
		Fullscreen,
		Windowed,
		WindowedFullscreen,
	};


	export struct WindowDesc
	{
		std::string title = "Lys";
		Vec2u dimensions{1280, 720};

		WindowState state{WindowState::Windowed};

		bool resizable{true};
		bool visible{true};
		bool vsync{true};
	};


	export class Window
	{
		static inline bool s_glfwInitialized{false};

		GLFWwindow* m_glfwWindow{nullptr};
		WindowDesc m_desc{};

	public:
		Window();
		explicit Window(const WindowDesc& desc);

		~Window() = default;

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		Window(Window&& other) noexcept;
		Window& operator=(Window&& other) noexcept;

	private:
		void initWindow();
		void initGLFW();
	};
} // namespace lys
