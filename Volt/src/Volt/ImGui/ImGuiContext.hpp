#pragma once

#include <memory>

//Forward declaration
namespace Volt
{
    class Window;
}

namespace Volt::GUI
{
    //ImGui Context Interface
    class ImGuiContext
    {
    public:
        typedef std::unique_ptr<ImGuiContext> ImGuiPtr;

    public:
        static ImGuiPtr CreateContext(Volt::Window *native_window);

    public:
        ImGuiContext() {}
        virtual ~ImGuiContext() {}

    public:
        virtual void BeginDraw() = 0;
        virtual void EndDraw() = 0;
    };
}