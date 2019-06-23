#pragma once

#include "Volt/Logger.hpp"
#include "Volt/Window/Window.hpp"
#include "Volt/LayerStack.hpp"

namespace Volt {

    // Logic instance of our program
    class Application
    {
    public:

        Application(int _argc, char **_argv);
        virtual ~Application();

    public:
        void Run();
        void Stop();

        inline void PushLayer(Layer::LayerPtr layer) { m_renderingLayerStack.PushLayer(std::move(layer)); }
        inline void PushOverlay(Layer::LayerPtr layer) { m_renderingLayerStack.PushOverlay(std::move(layer)); }

    protected:
        //TODO: add delta time
        virtual void OnUpdate() = 0;

    private:
        bool                    m_running;
        Volt::Window::WindowPtr m_window;
        LayerStack              m_renderingLayerStack;
    };

    Application *CreateApplication(int argc, char **argv);
}