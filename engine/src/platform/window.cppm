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
#ifdef LYS_VULKAN
#	define GLFW_INCLUDE_VULKAN
#endif
#include <GLFW/glfw3.h>
export module lys:window;

import :input_manager;
import :input_map;
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
		Vec2u		dimensions{1280, 720};

		WindowState state{WindowState::Windowed};

		bool resizable{true};
		bool visible{true};
		bool focused{true};
		bool vsync{true};
	};

	export enum class WindowHint : std::int32_t
	{
		RedBits			 = GLFW_RED_BITS,
		GreenBits		 = GLFW_GREEN_BITS,
		BlueBits		 = GLFW_BLUE_BITS,
		AlphaBits		 = GLFW_ALPHA_BITS,
		DepthBits		 = GLFW_DEPTH_BITS,
		StencilBits		 = GLFW_STENCIL_BITS,
		RefreshRate		 = GLFW_REFRESH_RATE,
		Samples			 = GLFW_SAMPLES,
		ScaleToMonitor	 = GLFW_SCALE_TO_MONITOR,
		ScaleFramebuffer = GLFW_SCALE_FRAMEBUFFER,
		SRGBCapable		 = GLFW_SRGB_CAPABLE,
	};

	export class Window
	{
		static inline bool		  s_glfwInitialized{false};
		static inline std::size_t s_liveWindowCount{0};

		GLFWwindow* m_glfwWindow{nullptr};
		WindowState m_state{WindowState::Windowed};

		Vec2i m_windowedPosition{100, 100};
		Vec2i m_windowedSize{1280, 720};
		bool  m_hasWindowedPlacement{false};
		bool  m_visible{true};

		InputManager m_inputManager;

	public:
		using WindowSizeCallback			= std::function<void(int width, int height)>;
		using WindowFramebufferSizeCallback = std::function<void(int width, int height)>;

	private:
		WindowSizeCallback			  m_windowSizeCallback{};
		WindowFramebufferSizeCallback m_windowFramebufferSizeCallback{};

	public:
		Window();
		explicit Window(const WindowDesc& desc);

		~Window();

		[[nodiscard]] inline GLFWwindow*   nativeHandle() const noexcept { return m_glfwWindow; }
		[[nodiscard]] inline InputManager& inputManager() noexcept { return m_inputManager; }
		[[nodiscard]] inline const InputManager& inputManager() const noexcept
		{
			return m_inputManager;
		}

		static inline void pollEvents() { glfwPollEvents(); }
		inline void		   update()
		{
			m_inputManager.update();
			m_inputManager.enableEventDispatch();
		}

		[[nodiscard]] inline bool shouldClose() const
		{
			return glfwWindowShouldClose(m_glfwWindow);
		}

		inline void close() const { glfwSetWindowShouldClose(m_glfwWindow, GLFW_TRUE); }

		static inline void terminate()
		{
			glfwTerminate();

			// Update glfw initialization status
			s_glfwInitialized = false;
		}

		[[nodiscard]] inline std::string title() const { return glfwGetWindowTitle(m_glfwWindow); }

		inline void setTitle(const std::string& title) const
		{
			glfwSetWindowTitle(m_glfwWindow, title.c_str());
		}

		[[nodiscard]] inline Vec2i dimensions() const
		{
			Vec2i size{};
			glfwGetWindowSize(m_glfwWindow, &size.x, &size.y);
			return size;
		}
		[[nodiscard]] inline Vec2i framebufferDimensions() const
		{
			Vec2i size;
			glfwGetFramebufferSize(m_glfwWindow, &size.x, &size.y);
			return size;
		}

		void inline setDimensions(const Vec2i& dimensions) const
		{
			glfwSetWindowSize(m_glfwWindow, dimensions.x, dimensions.y);
		}

		[[nodiscard]] inline float opacity() const { return glfwGetWindowOpacity(m_glfwWindow); }
		inline void				   setOpacity(const float alpha) const
		{
			glfwSetWindowOpacity(m_glfwWindow, alpha);
		}

		[[nodiscard]] WindowState state() const noexcept { return m_state; }
		void					  setState(WindowState state);

		inline void show()
		{
			glfwShowWindow(m_glfwWindow);
			m_visible = true;
		}

		inline void hide()
		{
			glfwHideWindow(m_glfwWindow);
			m_visible = false;
		}

		inline void focus() const { glfwFocusWindow(m_glfwWindow); }

		inline void requestAttention() const { glfwRequestWindowAttention(m_glfwWindow); }

		void minimize() const { throw std::runtime_error("Unimplemented function"); }

		void maximize() const { throw std::runtime_error("Unimplemented function"); }

		static void setResizable(const bool resizable)
		{
			glfwWindowHint(GLFW_RESIZABLE, resizable);
		}

		[[nodiscard]] inline bool isVisible() const { return m_visible; }

		static inline void setCursorMode(const CursorMode mode)
		{
			glfwWindowHint(GLFW_CURSOR, mode);
		}

		static inline void setHint(WindowHint hint, const std::int32_t value)
		{
			glfwWindowHint(static_cast<int>(hint), value);
		}

	private:
		void initWindow(const WindowDesc& desc = {});
		void initGLFW();
		void destroyWindow() const;
		void applyWindowHints() const;
		void registerCallbacks();

		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void cursorPosCallback(GLFWwindow* window, double xPos, double yPos);
		static void windowSizeCallback(GLFWwindow* window, int width, int height);
		static void windowFramebufferSizeCallback(GLFWwindow* window, int width, int height);
	};
} // namespace lys
