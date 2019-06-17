#include "vpch.h"
#include "Volt/Graphics/OpenGL/Context.hpp"

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

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