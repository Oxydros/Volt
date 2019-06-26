#include "vpch.h"

#include "Volt/Application.hpp"
#include "Volt/Logger.hpp"

namespace Volt
{

    Application::Application(int _argc, char **_argv)
        : m_running(true)
    {
        auto settings = Volt::WindowSettings("Sandbox Application", 800, 600);
        m_window = Volt::Window::CreateWindow(settings);
        m_window->InitializeImGuiContext();
    }

    Application::~Application()
    {}

    void Application::Run()
    {
        m_running = true;
        VOLT_INFO("Running...");
        while (m_running)
        {
            m_window->Clear();

            // Application logic
            OnUpdate();

            //Layer Update
            for (auto &layer : m_renderingLayerStack)
            {
                // VOLT_DEB("Calling OnUpdate for layer {}", layer->GetName());
                layer->OnUpdate();
            }

            //ImGui rendering
            m_window->ImGuiBegin();
            for (auto &layer : m_renderingLayerStack)
            {
                // VOLT_DEB("Calling OnImGUI for layer {}", layer->GetName());
                layer->OnImGUI();
            }
            m_window->ImGuiEnd();

            //Window poll event and buffer swap
            m_window->OnUpdate();
        }
    }

    void Application::Stop()
    {
        m_running = false;
    }
}