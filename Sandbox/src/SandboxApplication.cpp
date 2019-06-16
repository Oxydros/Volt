#include "SandboxApplication.hpp"

SandboxApplication::SandboxApplication(int _argc, char **_argv)
    : Volt::Application(_argc, _argv), m_running(true)
{
    VOLT_INFO("Launching Sandbox...");

    auto settings = Volt::WindowSettings("Sandbox Application", 800, 600);

    m_window = Volt::Window::CreateWindow(settings);
}

int SandboxApplication::Run()
{
    m_running = true;
    VOLT_INFO("Running...");
    while (m_running)
    {
        // Volt::Event::TestEvent test;
        // Volt::Event::DispatchEvent(test);
        m_window->onUpdate();
    }
    return 0;
}

void SandboxApplication::Stop()
{
    m_running = false;
}

bool SandboxApplication::handleEvent(Volt::Event::KeyPressedEvent const &event)
{
    VOLT_INFO("Got keyboard pressed key event {} !", event.GetKeyCode());
    return true;
}

bool SandboxApplication::handleEvent(Volt::Event::WindowClosedEvent const &event)
{
    VOLT_INFO("Window closed event ! Stopping application");
    Stop();
    return true;
}


// -- Entry point
Volt::Application *Volt::CreateApplication(int argc, char **argv)
{
    return new SandboxApplication(argc, argv);
}