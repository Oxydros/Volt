#pragma once

#include "Volt.hpp"
#include "Volt/Window/Window.hpp"

class SandboxApplication : public Volt::Application, public Volt::Event::EventListener<Volt::Event::TestEvent>
{
public:
    SandboxApplication(int _argc, char **_argv);
    virtual ~SandboxApplication() {}

    int Run() override;

    bool handleEvent(Volt::Event::TestEvent const &event) override
    {
        event.testFunction();
        return false;
    }

private:
    bool                    m_running;
    Volt::Window::WindowPtr m_window;
};