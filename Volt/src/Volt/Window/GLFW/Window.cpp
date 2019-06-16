#include "Volt/Window/GLFW/Window.hpp"

namespace Volt
{
    bool GLFW::Window::Window::GLFW_Initialized = false;

    GLFW::Window::Window(Volt::WindowSettings const &settings)
        : Volt::Window(settings)
    {
        if (!GLFW_Initialized)
        {
            if (glfwInit() != GLFW_TRUE)
            {
                throw Volt::WindowCreationException("Couldn't initialize GLFW");
            }

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            GLFW_Initialized = true;
        }

        m_window = glfwCreateWindow(settings.Width, settings.Height, settings.Name.c_str(), NULL, NULL);
        if (m_window == NULL)
        {
            glfwTerminate();
            throw Volt::WindowCreationException("Failed to create GLFW window");
        }

        m_context = new Graphics::OpenGL::Context(m_window);
        if (!m_context->Initialize())
        {
            glfwTerminate();
            throw Volt::ContextCreationException("Failed to initialize OpenGL Context");
        }
    }

    GLFW::Window::~Window()
    {
        //Delete context here -- TODO: smart pointers
        delete m_context;
        glfwDestroyWindow(m_window);
        //-- for now destroy GLFW, do not support multi windows
        glfwTerminate();
    }

    void GLFW::Window::onUpdate()
    {
        m_context->SwapBuffers();
        glfwPollEvents();
    }

    //--Creation of window routine
    Window::WindowPtr Volt::Window::CreateWindow(WindowSettings const &settings)
    {
        return std::make_unique<Volt::GLFW::Window>(settings);
    }
}