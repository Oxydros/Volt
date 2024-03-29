#include "SandboxApplication.hpp"
#include "ImGuiLayer.hpp"

#include <glad/glad.h>

SandboxApplication::SandboxApplication(int _argc, char **_argv)
    : Volt::Application(_argc, _argv)
{
    VOLT_INFO("Launching Sandbox...");
    auto imGuiLayer = Volt::Layer::Create<ImGuiLayer>();

    Application::PushOverlay(imGuiLayer);
}

void SandboxApplication::OnUpdate()
{
}

bool SandboxApplication::handleEvent(Volt::Event::KeyPressedEvent const &event)
{
    VOLT_INFO("Got keyboard pressed key event {} !", event.GetKeyCode());
    switch (event.GetKeyCode()){
        case VOLT_KEY_ESCAPE:
        {
            Stop();
            return true;
        }
        case VOLT_KEY_F:
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            return true;
        }
        case VOLT_KEY_G:
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            return true;
        }
    }
    return false;
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