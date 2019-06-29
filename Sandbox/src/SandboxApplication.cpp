#include "SandboxApplication.hpp"
#include "ImGuiLayer.hpp"

#include <glad/glad.h>

char vertexShaderSrc[] =
R"(
#version 400 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec4 inColor;

out vec4 vertexColor;

void main()
{
    gl_Position = vec4(inPos.x, inPos.y, inPos.z, 1.0);
    vertexColor = inColor;
}
)";

char pixelShaderSrc[] =
R"(
#version 330 core
out vec4 pixelColor;

in vec4 vertexColor;

uniform vec4 ourColor;

void main()
{
    pixelColor = ourColor;
}
)";

SandboxApplication::SandboxApplication(int _argc, char **_argv)
    : Volt::Application(_argc, _argv)
{
    VOLT_INFO("Launching Sandbox...");
    // auto imGuiLayer = Volt::Layer::Create<ImGuiLayer>();

    // Application::PushOverlay(imGuiLayer);

    m_shader = Volt::Graphics::Shader::CreateShader(vertexShaderSrc, pixelShaderSrc);

    m_vertexArray = Volt::Graphics::VertexArray::Create();

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,// Bot L
        0.5f, -0.5f, 0.0f, 0.2f, 0.2f, 0.2f, 1.0f, // Bot R
        // 0.0f,  0.5f, 0.0f, // Top
        -0.5f, 0.5f, 0.0f, 0.2f, 0.8f, 0.3f, 1.0f,//Top L
        0.5f, 0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,// Top R
    };

    auto vertexBuffer = Volt::Graphics::VertexBuffer::Create(vertices, sizeof(vertices) / sizeof(float));
    vertexBuffer->SetLayout({
        {Volt::Graphics::VertexElementType::VEC_3F},
        {Volt::Graphics::VertexElementType::VEC_4F}
    });
    m_vertexArray->AddVertexBuffer(vertexBuffer);

    int indices[] = {
        2, 0, 1,
        3, 2, 1
    };
    auto indexBuffer = Volt::Graphics::IndexBuffer::Create(indices, sizeof(indices) / sizeof(int));
    m_vertexArray->SetIndexBuffer(indexBuffer);

    m_vertexArray->Unbind();

    m_shader->SetVec4f("ourColor", glm::vec4(0.2f, 0.4f, 0.3f, 1.0f));
}

void SandboxApplication::OnUpdate()
{
    m_shader->Bind();
    m_vertexArray->Bind();

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