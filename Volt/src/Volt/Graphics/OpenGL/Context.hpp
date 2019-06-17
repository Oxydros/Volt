#pragma once

#include "Volt/Graphics/IContext.hpp"

//Foreward declaration to not include GLFW here
//Or else problem with ImGui includes
struct GLFWwindow;

namespace Volt::Graphics::OpenGL
{
    class Context : public Volt::Graphics::IContext
    {
    public:
        Context(GLFWwindow *glfw_window);
        virtual ~Context();

    public:
        bool Initialize() override;
        void SwapBuffers() override;

    private:
        GLFWwindow      *m_window;
    };
}