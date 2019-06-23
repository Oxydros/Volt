#pragma once

#include "Volt/Graphics/OpenGL/Context.hpp"
#include "Volt/Window/Window.hpp"

#include "Volt/ImGui/ImGuiContext.hpp"

//--- GLFW specicific namespace
namespace Volt::GLFW {

    class Window : public Volt::Window
    {
    public:
        Window(WindowSettings const &settings);
        virtual ~Window();

    public:
        void InitializeImGuiContext() override;
        void ImGuiBegin() override;
        void ImGuiEnd() override;

        void OnUpdate() override;
        inline Volt::Graphics::IContext *GetGraphicContext() override { return m_context; }
        inline void *GetRawWindow() const override { return m_window; }

    private:
        static bool                 GLFW_Initialized;
        Graphics::OpenGL::Context   *m_context;
        GLFWwindow                  *m_window;
        GUI::ImGuiContext::ImGuiPtr m_imGuiContext;
    };
}