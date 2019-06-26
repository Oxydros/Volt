#include "SandboxApplication.hpp"
#include "ImGuiLayer.hpp"

#include <glad/glad.h>

char vertexShaderSrc[] =
R"(
#version 400 core

layout (location = 0) in vec3 inPos;

void main()
{
    gl_Position = vec4(inPos.x, inPos.y, inPos.z, 1.0);
}
)";

char pixelShaderSrc[] =
R"(
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
)";


int CompileShader(char *shaderSrc, GLenum shaderType)
{
    unsigned int shaderId = glCreateShader(shaderType);
    VOLT_ASSERT(shaderId != 0, "Couldn't create GL Shader")

    glShaderSource(shaderId, 1, &shaderSrc, NULL);
    glCompileShader(shaderId);

    int  success;
    char infoLog[512];
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
        VOLT_ASSERT(false, "Error while COMPILING shader : {}", infoLog);
    }
    return shaderId;
}

SandboxApplication::SandboxApplication(int _argc, char **_argv)
    : Volt::Application(_argc, _argv)
{
    VOLT_INFO("Launching Sandbox...");
    // auto imGuiLayer = Volt::Layer::Create<ImGuiLayer>();

    // Application::PushOverlay(imGuiLayer);

    int vertexShader = CompileShader(vertexShaderSrc, GL_VERTEX_SHADER);
    int pixelShader = CompileShader(pixelShaderSrc, GL_FRAGMENT_SHADER);

    m_shaderProgram = glCreateProgram();

    glAttachShader(m_shaderProgram, vertexShader);
    glAttachShader(m_shaderProgram, pixelShader);
    glLinkProgram(m_shaderProgram);

    int  success;
    char infoLog[512];
    glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog);
        VOLT_ASSERT(false, "Error while LINKING shaders in program : {}", infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(pixelShader);

    glGenVertexArrays(1, &m_vertexArrayObj);
    glBindVertexArray(m_vertexArrayObj);

    static float vertices[] = {
        -0.5f, -0.5f, 0.0f, // Bot L
        0.5f, -0.5f, 0.0f, // Bot R
        // 0.0f,  0.5f, 0.0f, // Top
        -0.5f, 0.5f, 0.0f, //Top L
        0.5f, 0.5f, 0.0f // Top R
    };

    //Create buffer and bind it
    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    //Fill it
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  

    static int indices[] = {
        2, 0, 1,
        3, 2, 1
    };

    glGenBuffers(1, &m_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //Unbind
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void SandboxApplication::OnUpdate()
{
    glUseProgram(m_shaderProgram);
    glBindVertexArray(m_vertexArrayObj);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

bool SandboxApplication::handleEvent(Volt::Event::KeyPressedEvent const &event)
{
    VOLT_INFO("Got keyboard pressed key event {} !", event.GetKeyCode());
    switch (event.GetKeyCode()){
        case VOLT_KEY_ESCAPE:
            {
                Stop();
                break;
            }
        case VOLT_KEY_F:
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            break;
        }
        case VOLT_KEY_G:
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            break;
        }
    }
    return true;
}

bool SandboxApplication::handleEvent(Volt::Event::WindowClosedEvent const &event)
{
    VOLT_INFO("Window closed event ! Stopping application");
    Application::Stop();
    return true;
}

bool SandboxApplication::handleEvent(Volt::Event::WindowMovedEvent const &event)
{
    VOLT_INFO("Window Moved ! New pos: {} {}", event.GetX(), event.GetY());
    return true;
}

bool SandboxApplication::handleEvent(Volt::Event::WindowResizeEvent const &event)
{
    VOLT_INFO("Window resized ! New size: {} {}", event.GetWidth(), event.GetHeight());
    return true;
}


// -- Entry point
Volt::Application *Volt::CreateApplication(int argc, char **argv)
{
    return new SandboxApplication(argc, argv);
}