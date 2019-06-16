#pragma once

#include "Volt/Graphics/OpenGL/Context.hpp"
#include "Volt/Window/Window.hpp"


//--- GLFW specicific namespace
namespace Volt::GLFW {

    class Window : public Volt::Window
    {
    public:
        Window(WindowSettings const &settings);
        virtual ~Window();

    public:
        void onUpdate() override;
        inline Volt::Graphics::IContext *getGraphicContext() override { return m_context; }

    private:
        static bool                 GLFW_Initialized;
        Graphics::OpenGL::Context   *m_context;
        GLFWwindow                  *m_window;
    };
}