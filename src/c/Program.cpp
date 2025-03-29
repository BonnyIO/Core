#include "../h/Program.hpp"
#include "../h/Window.hpp"
#include "../h/Event.hpp"
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

        m_dispaccher.event_listener<EventMouseMoved>([](EventMouseMoved& event) {

            LOG_INFO("[MouseMoved] Mouse moved to {0}x{1}", event.x, event.y);

        });

        m_dispaccher.event_listener<EventWindowResize>([](EventWindowResize& event) {

            LOG_INFO("[Resized] Changed size to {0}x{1}", event.width, event.height);

        });

        m_dispaccher.event_listener<EventWindowClose>([&](EventWindowClose& event) {

            LOG_INFO("[Window Close]");
            closeWindow = true;

        });

        m_window->setEventCallback([&](BaseEvent& event) {
            
            m_dispaccher.dispatch(event);
            
        });

        while (!closeWindow) {

            m_window->gameUpdate();
           
            on_update();
        }

        m_window = nullptr;

        return 0;
    }
}