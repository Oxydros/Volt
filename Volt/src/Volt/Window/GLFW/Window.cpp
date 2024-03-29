#include "vpch.h"

// -- Volt
#include "Volt/Window/GLFW/Window.hpp"
#include "Volt/ImGui/GLFW/ImGuiContext.hpp"
#include "Volt/Event.hpp"

// -- Glad and GLFW
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

namespace Volt::GLFW
{

    static void GLFWErrorCallback(int error, const char* description)
    {
        VOLT_ERROR("GLFW Error[{}]: {}", error, description);
    }

    bool GLFW::Window::Window::GLFW_Initialized = false;

    GLFW::Window::Window(Volt::WindowSettings const &settings)
        : Volt::Window(settings)
    {
        if (!GLFW_Initialized)
        {
            glfwSetErrorCallback(GLFWErrorCallback);
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

        //
        // -- Setup callbacks
        // -- See https://www.glfw.org/docs/latest/input_guide.html#events
        //
        glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods){

            switch (action)
            {
                case GLFW_PRESS:
                {
                    Event::KeyPressedEvent event(key);
                    Event::DispatchEvent(event);
                    break;
                }

                case GLFW_RELEASE:
                {
                    Event::KeyReleasedEvent event(key);
                    Event::DispatchEvent(event);
                    break;
                }

                case GLFW_REPEAT:
                {
                    Event::KeyPressedEvent event(key, true);
                    Event::DispatchEvent(event);
                    break;
                }
            }
        });

        glfwSetCharCallback(m_window, [](GLFWwindow* window, unsigned int codepoint){
            Event::KeyTypedEvent event(codepoint);
            Event::DispatchEvent(event);
        });

        glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height){
            Event::WindowResizeEvent event(width, height);
            Event::DispatchEvent(event);
        });

        glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window){
            Event::WindowClosedEvent event;
            Event::DispatchEvent(event);
        });

        glfwSetWindowPosCallback(m_window, [](GLFWwindow* window, int xpos, int ypos){
            Event::WindowMovedEvent event(xpos, ypos);
            Event::DispatchEvent(event);
        });

        glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods){
            switch (action)
            {
                case GLFW_PRESS:
                {
                    Event::MouseButtonPressedEvent event(button);
                    Event::DispatchEvent(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    Event::MouseButtonReleasedEvent event(button);
                    Event::DispatchEvent(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xoffset, double yoffset){
            Event::MouseScrolledEvent event(xoffset, yoffset);
            Event::DispatchEvent(event);
        });

        glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos){
            Event::MouseMovedEvent event(xpos, ypos);
            Event::DispatchEvent(event);
        });
    }

    GLFW::Window::~Window()
    {
        //Force deletion before context or else we get a segfault
        m_imGuiContext.reset();
        //Delete context here -- TODO: smart pointers
        delete m_context;
        glfwDestroyWindow(m_window);
        //-- for now destroy GLFW, do not support multi windows
        glfwTerminate();
    }

    void GLFW::Window::InitializeImGuiContext()
    {
        m_imGuiContext = Volt::GUI::ImGuiContext::CreateContext(this);
    }

    void GLFW::Window::ImGuiBegin()
    {
        if (m_imGuiContext)
            m_imGuiContext->BeginDraw();
    }

    void GLFW::Window::ImGuiEnd()
    {
        if (m_imGuiContext)
            m_imGuiContext->EndDraw();
    }

    void GLFW::Window::Clear()
    {
		glClearColor(0.1f, 0.1f, 0.1f, 1);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    }

    void GLFW::Window::OnUpdate()
    {
        glfwPollEvents();
        m_context->SwapBuffers();
    }
}

//--Creation of window routine
Volt::Window::WindowPtr Volt::Window::CreateWindow(WindowSettings const &settings)
{
    return std::make_unique<Volt::GLFW::Window>(settings);
}