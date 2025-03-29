#pragma once
#include "../h/Event.hpp"
#include <memory>

namespace Core {

	class Program {

	public:

		Program();
		virtual ~Program();

		Program(const Program&) = delete;
		Program(Program&&) = delete;
		Program& operator=(const Program&) = delete;
		Program& operator=(Program&&) = delete;

		virtual int start(unsigned int windowWidth, unsigned int windowHeidht, const char* title);

		virtual void on_update() {};

	private:

		std::unique_ptr<class Window> m_window;
		EventDispatcher m_dispaccher;
		bool closeWindow = false;
	};
}