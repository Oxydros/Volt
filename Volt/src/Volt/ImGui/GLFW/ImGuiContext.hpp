#pragma once

#include "Volt/ImGui/ImGuiContext.hpp"

namespace Volt::GLFW::GUI
{
    class ImGuiContext : public Volt::GUI::ImGuiContext
    {
    public:
        ImGuiContext(Volt::Window *window);
        virtual ~ImGuiContext();

    public:
        void BeginDraw() override;
        void EndDraw() override;

    private:
        Volt::Window *m_window;
    };
}