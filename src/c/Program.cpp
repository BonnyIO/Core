#include "../h/Program.hpp"
#include "../h/Window.hpp"
#include "../h/Log.hpp"


#include <iostream>

namespace Core {

    Program::Program() {

        LOG_INFO("Sarting Program");
    }
    Program::~Program() {

        LOG_INFO("Closing Program");
    }

    int Program::start(unsigned int windowWidth, unsigned int windowHeidht, const char* title) {

        m_window = std::make_unique<Window>(title, windowWidth, windowHeidht);

        m_window->setEventCallback([](Event& event){LOG_INFO("[EVENT] Changed size to {0}x{1}", event.width, event.height);});

        while (true) {

            m_window->gameUpdate();
           
            on_update();
        }

        return 0;
    }
}