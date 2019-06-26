#include "vpch.h"

#include "Volt/Graphics/OpenGL/Context.hpp"

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

//Callback for error messages
void GLAPIENTRY
OpenGLGraphicContextError( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
    auto header_type = type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "";
    VOLT_ERROR("GL CALLBACK: {} type = 0x{:x}, severity = 0x{:x}, message = {}",
        header_type, type, severity, message );
}

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
        if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0)
            return false;

#ifdef VOLT_DEBUG
        glEnable              ( GL_DEBUG_OUTPUT );
        glDebugMessageCallback( OpenGLGraphicContextError, 0 );
#endif
        return true;
    }

    void Context::SwapBuffers()
    {
        glfwSwapBuffers(m_window);
    }
}