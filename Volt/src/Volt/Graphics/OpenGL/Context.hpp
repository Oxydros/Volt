#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "Volt/Graphics/IContext.hpp"

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