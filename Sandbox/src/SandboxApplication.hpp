#pragma once

#include "Volt.hpp"
#include "Volt/Window/Window.hpp"

class SandboxApplication : public Volt::Application,
    public Volt::Event::EventListener<Volt::Event::KeyPressedEvent>,
    public Volt::Event::EventListener<Volt::Event::WindowClosedEvent>
{
public:
    SandboxApplication(int _argc, char **_argv);
    virtual ~SandboxApplication() {}

    void Stop();
    int Run() override;

    bool handleEvent(Volt::Event::KeyPressedEvent const &event) override;
    bool handleEvent(Volt::Event::WindowClosedEvent const &event) override;

private:
    bool                    m_running;
    Volt::Window::WindowPtr m_window;
};