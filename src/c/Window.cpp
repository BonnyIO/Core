#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "../h/Log.hpp"
#include "../h/Window.hpp"
#include <iostream>

namespace Core {

	Window::Window(std::string title, const unsigned int width, const unsigned int height) : m_data({ std::move(title), width, height }) {

		int resultCode = init();
	}

	Window::~Window() {

		shutdown();
	}

	int Window::init() {

		if (!glfwInit()) {

			LOG_CRITICAL("ERROR GLFWINIT!");
			return -1;
		}

		m_window = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), NULL, NULL);

		if (!m_window) {

			LOG_CRITICAL("ERROR create window! {0} width size {1}x{2}", m_data.title, m_data.width, m_data.height);
			glfwTerminate();
			return -2;
		}

		glfwMakeContextCurrent(m_window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {

			LOG_CRITICAL("ERROR GLADINIT!");
			return -3;
		}

		glfwSetWindowUserPointer(m_window, &m_data);

		glfwSetWindowSizeCallback(m_window,[](GLFWwindow* window, int width, int haight) {
			
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			data.width = width;
			data.height = haight;

			EventWindowResize event(width, haight);
			data.eventCallback(event);

		});

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {

			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			EventWindowClose event;
			data.eventCallback(event);

		});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double x, double y) {

			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			EventMouseMoved event(x, y);
			data.eventCallback(event);

			});

		return 0;
	}

	void Window::shutdown() {

		glfwDestroyWindow(m_window);
		glfwTerminate();
	}

	void Window::gameUpdate() {

		glClearColor(0, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

}
