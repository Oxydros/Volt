#include "imgui.h"

#include "ImGuiLayer.hpp"
#include "Volt/Logger.hpp"
#include "Volt/KeyCode.h"

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <stb_image.h>

char vertexShaderSrc[] =
R"(
#version 400 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec4 inColor;
layout (location = 2) in vec2 inTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 vertexColor;
out vec2 TexCoord;

void main()
{
    gl_Position = projection * view * model * vec4(inPos, 1.0);
    vertexColor = inColor;
    TexCoord = inTexCoord;
}
)";

char pixelShaderSrc[] =
R"(
#version 330 core
out vec4 pixelColor;

in vec4 vertexColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;

uniform float mix_ratio;

void main()
{
    pixelColor = mix(texture(ourTexture, TexCoord), texture(ourTexture2, TexCoord), mix_ratio);
}
)";

ImGuiLayer::ImGuiLayer() : Layer("ImGui")
{
    m_shader = Volt::Graphics::Shader::CreateShader(vertexShaderSrc, pixelShaderSrc);

    m_vertexArray = Volt::Graphics::VertexArray::Create();

    float vertices[] = {
        // front
        -0.5, -0.5,  0.5, 1.0, 0.0, 0.0, 1.0, 0.0f, 0.0f,
        0.5, -0.5,  0.5, 0.0, 1.0, 0.0, 1.0, 1.0f, 0.0f,
        0.5,  0.5,  0.5, 0.0, 0.0, 1.0, 1.0, 1.0f, 1.0f,
        -0.5,  0.5,  0.5, 1.0, 1.0, 1.0, 1.0, 0.0f, 1.0f,
        // back
        -0.5, -0.5, -0.5, 1.0, 0.0, 0.0, 1.0, 0.0f, 0.0f,
        0.5, -0.5, -0.5, 0.0, 1.0, 0.0, 1.0, 1.0f, 0.0f,
        0.5,  0.5, -0.5, 0.0, 0.0, 1.0, 1.0, 1.0f, 1.0f,
        -0.5,  0.5, -0.5, 1.0, 1.0, 1.0, 1.0, 0.0f, 1.0f,
        // -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,// Bot L
        // 0.5f, -0.5f, 0.0f, 0.2f, 0.2f, 0.2f, 1.0f, // Bot R
        // // 0.0f,  0.5f, 0.0f, // Top
        // -0.5f, 0.5f, 0.0f, 0.2f, 0.8f, 0.3f, 1.0f,//Top L
        // 0.5f, 0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,// Top R
    };

    auto vertexBuffer = Volt::Graphics::VertexBuffer::Create(vertices, sizeof(vertices) / sizeof(float));
    vertexBuffer->SetLayout({
        {Volt::Graphics::VertexElementType::VEC_3F},
        {Volt::Graphics::VertexElementType::VEC_4F},
        {Volt::Graphics::VertexElementType::VEC_2F},
    });
    m_vertexArray->AddVertexBuffer(vertexBuffer);

    int indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
    };
    auto indexBuffer = Volt::Graphics::IndexBuffer::Create(indices, sizeof(indices) / sizeof(int));
    m_vertexArray->SetIndexBuffer(indexBuffer);

    m_vertexArray->Unbind();

    glViewport(0, 0, 800, 600);
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    m_shader->SetMat4f("projection", projection);

    m_rot = glm::vec4(0);
    m_pos = glm::vec3(0);
    m_mousePressed = false;

    m_texture1 = Volt::Graphics::Texture::CreateFromFile("Sandbox/res/container.jpg", false);
    m_texture1->SetXWrap(Volt::Graphics::TextureWrap::REPEAT);
    m_texture1->SetYWrap(Volt::Graphics::TextureWrap::REPEAT);
    m_texture1->SetMinify(Volt::Graphics::TextureMin::LINEAR);
    m_texture1->SetMagnify(Volt::Graphics::TextureMag::LINEAR);

    m_texture2 = Volt::Graphics::Texture::CreateFromFile("Sandbox/res/awesomeface.png");
    m_texture2->SetXWrap(Volt::Graphics::TextureWrap::REPEAT);
    m_texture2->SetYWrap(Volt::Graphics::TextureWrap::REPEAT);
    m_texture2->SetMinify(Volt::Graphics::TextureMin::LINEAR);
    m_texture2->SetMagnify(Volt::Graphics::TextureMag::LINEAR);

    m_shader->SetInt("ourTexture", 0);
    m_shader->SetInt("ourTexture2", 1);
    m_mix = 0.2f;
}

ImGuiLayer::~ImGuiLayer()
{}

void ImGuiLayer::OnUpdate()
{
    m_camera.Update();

    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, m_pos);
    model = glm::rotate(model, glm::radians(m_rot.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(m_rot.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(m_rot.z), glm::vec3(0.0f, 0.0f, 1.0f));

    m_texture1->Bind(0);
    m_texture2->Bind(1);
    m_shader->Bind();
    m_vertexArray->Bind();

    m_shader->SetFloat("mix_ratio", m_mix);
    m_shader->SetMat4f("model", model);
    m_shader->SetMat4f("view", m_camera.GetViewMatrix());

    glDrawElements(GL_TRIANGLES, m_vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
}

void ImGuiLayer::OnImGUI()
{
    ImGui::Begin("Scene controls");

    ImGui::SliderFloat("Texture Mix", &m_mix, 0.0f, 1.0f);
    ImGui::NewLine();
    ImGui::SliderFloat("X rotation", &m_rot.x, -180.0f, 180.0f);
    ImGui::SliderFloat("Y rotation", &m_rot.y, -180.0f, 180.0f);
    ImGui::SliderFloat("Z rotation", &m_rot.z, -180.0f, 180.0f);
    ImGui::NewLine();
    ImGui::SliderFloat("X Position", &m_pos.x, -20.0f, 10.0f);
    ImGui::SliderFloat("Y Position", &m_pos.y, -20.0f, 10.0f);
    ImGui::SliderFloat("Z Position", &m_pos.z, -20.0f, 10.0f);
    ImGui::NewLine();
    if (ImGui::Button("Reset cube position"))
        m_pos = glm::vec3(0);

    if (ImGui::Button("Reset cube orientation"))
        m_rot = glm::vec4(0);

    if (ImGui::Button("Reset camera orientation"))
        m_camera.SetOrientation(glm::vec3(0));
    if (ImGui::Button("Reset camera position"))
        m_camera.SetPosition(glm::vec3(0, 0, -5));        

    ImGui::SameLine();
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}

bool ImGuiLayer::handleEvent(Volt::Event::KeyPressedEvent const &event)
{
    switch (event.GetKeyCode())
    {
        case VOLT_KEY_W:
        {
            m_camera.GetPosition() += m_camera.GetForward();
            return true;
        }
        case VOLT_KEY_S:
        {
            m_camera.GetPosition() -= m_camera.GetForward();
            return true;
        }
        case VOLT_KEY_A:
        {
            m_camera.GetPosition() -= m_camera.GetRightSide();
            return true;
        }
        case VOLT_KEY_D:
        {
            m_camera.GetPosition() += m_camera.GetRightSide();
            return true;
        }
    }
    return false;
}

bool ImGuiLayer::handleEvent(Volt::Event::MouseMovedEvent const &event)
{
    if (m_mousePressed == false)
        return false;

    m_camera.FeedMouseInput(event.GetX(), event.GetY());
    return false;
}

bool ImGuiLayer::handleEvent(Volt::Event::MouseButtonPressedEvent const &event)
{
    m_mousePressed = true;
    VOLT_DEB("Got mouse Pressed event ! {}", event.GetButton());
    return false;
}

bool ImGuiLayer::handleEvent(Volt::Event::MouseButtonReleasedEvent const &event)
{
    m_mousePressed = false;
    VOLT_DEB("Got mouse release event ! {}", event.GetButton());
    return false;
}
