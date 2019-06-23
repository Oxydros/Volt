#include "SandboxApplication.hpp"
#include "ImGuiLayer.hpp"

SandboxApplication::SandboxApplication(int _argc, char **_argv)
    : Volt::Application(_argc, _argv)
{
    VOLT_INFO("Launching Sandbox...");
    auto imGuiLayer = Volt::Layer::Create<ImGuiLayer>();

    Application::PushOverlay(imGuiLayer);
}

void SandboxApplication::OnUpdate()
{
    // Volt::Event::TestEvent test;
    // Volt::Event::DispatchEvent(test);
}

bool SandboxApplication::handleEvent(Volt::Event::KeyPressedEvent const &event)
{
    VOLT_INFO("Got keyboard pressed key event {} !", event.GetKeyCode());
    return true;
}

bool SandboxApplication::handleEvent(Volt::Event::WindowClosedEvent const &event)
{
    VOLT_INFO("Window closed event ! Stopping application");
    Application::Stop();
    return true;
}

bool SandboxApplication::handleEvent(Volt::Event::WindowMovedEvent const &event)
{
    VOLT_INFO("Window Moved ! New pos: {} {}", event.GetX(), event.GetY());
    return true;
}

bool SandboxApplication::handleEvent(Volt::Event::WindowResizeEvent const &event)
{
    VOLT_INFO("Window resized ! New size: {} {}", event.GetWidth(), event.GetHeight());
    return true;
}


// -- Entry point
Volt::Application *Volt::CreateApplication(int argc, char **argv)
{
    return new SandboxApplication(argc, argv);
}