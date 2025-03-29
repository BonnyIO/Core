#pragma once

#include "../h/Event.hpp"
#include <functional>
#include <string>

struct GLFWwindow;

namespace Core {

	class Window {

	public:

		using EventCallback = std::function<void(BaseEvent&)>;

		Window(std::string title, const unsigned int width, const unsigned int height);
		~Window();

		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator=(const Window&) = delete;
		Window& operator=(Window&&) = delete;

		void gameUpdate();
		unsigned int getWidth() const { return m_data.width; }
		unsigned int getHeight() const { return m_data.height; }
		void setEventCallback(const EventCallback callback) { m_data.eventCallback = callback;}

	private:

		struct WindowData {

			std::string title;
			unsigned int width;
			unsigned int height;
			EventCallback eventCallback;
		};

		int init();
		void shutdown();

		WindowData m_data;
		GLFWwindow* m_window = nullptr;
	};
}