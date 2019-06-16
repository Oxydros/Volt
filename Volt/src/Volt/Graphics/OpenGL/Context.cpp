#include "vpch.h"
#include "Volt/Graphics/OpenGL/Context.hpp"

namespace Volt::Graphics::OpenGL
{
    Context::Context(GLFWwindow *glfw_window)
        : m_window(glfw_window)
    {
    }

    Context::~Context()
    {}

    bool Context::Initialize()
    {
        glfwMakeContextCurrent(m_window);

        // -- gladLoadGLLoader return 0 for failure
        return gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) != 0;
    }

    void Context::SwapBuffers()
    {
        glfwSwapBuffers(m_window);
    }
}