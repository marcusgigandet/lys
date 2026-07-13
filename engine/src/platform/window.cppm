/*
 * Copyright 2026 Marcus Gigandet
 *
 * All rights reserved.
 */

module;
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan_core.h>
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
		bool focused{true};
		bool decorated{true};
		bool autoIconify{true};
		bool floating{false};
		bool maximized{false};
		bool transparentFramebuffer{false};
		bool vsync{true};

		std::optional<std::array<int, 2>> position{};
		std::optional<Vec2u> minDimensions{};
		std::optional<Vec2u> maxDimensions{};
		uint32_t samples{0};
	};

	export enum CursorMode
	{
		CURSOR_NORMAL = GLFW_CURSOR_NORMAL,
		CURSOR_HIDDEN = GLFW_CURSOR_HIDDEN,
		CURSOR_DISABLED = GLFW_CURSOR_DISABLED,
		CURSOR_CAPTURED = GLFW_CURSOR_CAPTURED,
		CURSOR_UNAVAILABLE = GLFW_CURSOR_UNAVAILABLE,
	};

	export enum class WindowHint : std::int32_t
	{
		RedBits = GLFW_RED_BITS,
		GreenBits = GLFW_GREEN_BITS,
		BlueBits = GLFW_BLUE_BITS,
		AlphaBits = GLFW_ALPHA_BITS,
		DepthBits = GLFW_DEPTH_BITS,
		StencilBits = GLFW_STENCIL_BITS,
		RefreshRate = GLFW_REFRESH_RATE,
		Samples = GLFW_SAMPLES,
		ScaleToMonitor = GLFW_SCALE_TO_MONITOR,
		ScaleFramebuffer = GLFW_SCALE_FRAMEBUFFER,
		SRGBCapable = GLFW_SRGB_CAPABLE,
	};

	export class Window
	{
		static inline bool s_glfwInitialized{false};
		static inline std::size_t s_liveWindowCount{0};

		GLFWwindow* m_glfwWindow{nullptr};
		WindowState m_state{WindowState::Windowed};

		std::array<int, 2> m_windowedPosition{100, 100};
		std::array<int, 2> m_windowedSize{1280, 720};
		bool m_hasWindowedPlacement{false};
		bool m_visible{true};

	public:
		using KeyCallback = std::function<void(int key, int scancode, int action, int mods)>;
		using MouseButtonCallback = std::function<void(int button, int action, int mods)>;
		using CursorPosCallback = std::function<void(double xPos, double yPos)>;
		using WindowSizeCallback = std::function<void(int width, int height)>;
		using WindowFramebufferSizeCallback = std::function<void(int width, int height)>;

	private:
		KeyCallback m_keyCallback{};
		MouseButtonCallback m_mouseButtonCallback{};
		CursorPosCallback m_cursorPosCallback{};
		WindowSizeCallback m_windowSizeCallback{};
		WindowFramebufferSizeCallback m_windowFramebufferSizeCallback{};

	public:
		Window();
		explicit Window(const WindowDesc& desc);

		~Window();

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		Window(Window&& other) noexcept;
		Window& operator=(Window&& other) noexcept;

		[[nodiscard]] inline GLFWwindow* nativeHandle() const noexcept { return m_glfwWindow; }

		static inline void pollEvents() { glfwPollEvents(); }

		[[nodiscard]] inline bool shouldClose() const
		{
			return glfwWindowShouldClose(m_glfwWindow);
		}

		inline void close() const { glfwSetWindowShouldClose(m_glfwWindow, GLFW_TRUE); }

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
		inline void setOpacity(const float alpha) const
		{
			glfwSetWindowOpacity(m_glfwWindow, alpha);
		}

		[[nodiscard]] WindowState state() const noexcept { return m_state; }
		void setState(const WindowState state);

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
