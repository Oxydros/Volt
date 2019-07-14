#include "imgui.h"

#include "ImGuiLayer.hpp"
#include "Volt/Logger.hpp"
#include "Volt/KeyCode.h"

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

ImGuiLayer::ImGuiLayer() : Layer("ImGui"), m_camera(45.0f, 800.0f / 600.0f, 0.1f, 100.0f)
{
    m_cubeShader = Volt::Graphics::Shader::CreateShader("./Sandbox/shaders/cubeShader.glsl");
    m_lightShader = Volt::Graphics::Shader::CreateShader("./Sandbox/shaders/lampShader.glsl");

    m_cubeArray = Volt::Graphics::VertexArray::Create();
    m_lightArray = Volt::Graphics::VertexArray::Create();

    float vertices[] = {
        // front
        -0.5, -0.5, 0.5, 0.0, 1.0, 1.0, 1.0,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
        0.5, -0.5, 0.5,  0.0, 1.0, 1.0, 1.0,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
        0.5, 0.5, 0.5,   0.0, 1.0, 1.0, 1.0,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
        -0.5, 0.5, 0.5,  0.0, 1.0, 1.0, 1.0,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
        // back
        -0.5, -0.5, -0.5, 1.0, 0.0, 1.0, 1.0,   0.0f, 0.0f,   0.0f, 0.0f, -1.0f,
        0.5, -0.5, -0.5,  1.0, 0.0, 1.0, 1.0,   1.0f, 0.0f,   0.0f, 0.0f, -1.0f,
        0.5, 0.5, -0.5,   1.0, 0.0, 1.0, 1.0,   1.0f, 1.0f,   0.0f, 0.0f, -1.0f,
        -0.5, 0.5, -0.5,  1.0, 0.0, 1.0, 1.0,   0.0f, 1.0f,   0.0f, 0.0f, -1.0f,
        //left
        -0.5, -0.5, -0.5,  1.0, 1.0, 0.0, 1.0,   0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
        -0.5, -0.5, 0.5,   1.0, 1.0, 0.0, 1.0,   1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
        -0.5, 0.5, 0.5,    1.0, 1.0, 0.0, 1.0,   1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
        -0.5, 0.5, -0.5,   1.0, 1.0, 0.0, 1.0,   0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
        //right
        0.5, -0.5, -0.5,  0.0, 0.0, 1.0, 1.0,   0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
        0.5, 0.5, -0.5,   0.0, 0.0, 1.0, 1.0,   1.0f, 1.0f,  1.0f, 0.0f, 0.0f,        
        0.5, 0.5, 0.5,    0.0, 0.0, 1.0, 1.0,   0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
        0.5, -0.5, 0.5,   0.0, 0.0, 1.0, 1.0,   1.0f, 0.0f,  1.0f, 0.0f, 0.0f,        
        //top
        -0.5, 0.5, -0.5,  0.0, 1.0, 0.0, 1.0,   0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
        -0.5, 0.5, 0.5,   0.0, 1.0, 0.0, 1.0,   1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
        0.5, 0.5, 0.5,    0.0, 1.0, 0.0, 1.0,   0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
        0.5, 0.5, -0.5,   0.0, 1.0, 0.0, 1.0,   1.0f, 1.0f,  0.0f, 1.0f, 0.0f,        
        //bottom
        -0.5, -0.5, 0.5,   1.0, 0.0, 0.0, 1.0,   1.0f, 0.0f,  0.0f, -1.0f, 0.0f,        
        -0.5, -0.5, -0.5,  1.0, 0.0, 0.0, 1.0,   0.0f, 0.0f,  0.0f, -1.0f, 0.0f,
        0.5, -0.5, -0.5,   1.0, 0.0, 0.0, 1.0,   1.0f, 1.0f,  0.0f, -1.0f, 0.0f,
        0.5, -0.5, 0.5,    1.0, 0.0, 0.0, 1.0,   0.0f, 1.0f,  0.0f, -1.0f, 0.0f,
    };

    int indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
        // back
		7, 6, 5,
		5, 4, 7,
        //left
        8, 9, 10,
        10, 11, 8,
        //right
        12, 13, 14,
        14, 15, 12,
        //top
        16, 17, 18,
        18, 19, 16,
        //bottom
        20, 21, 22,
        22, 23, 20
    };

    auto indexBuffer = Volt::Graphics::IndexBuffer::Create(indices, sizeof(indices) / sizeof(int));

    auto vertexBuffer = Volt::Graphics::VertexBuffer::Create(vertices, sizeof(vertices) / sizeof(float));
    vertexBuffer->SetLayout({
        {Volt::Graphics::VertexElementType::VEC_3F},
        {Volt::Graphics::VertexElementType::VEC_4F},
        {Volt::Graphics::VertexElementType::VEC_2F},
        {Volt::Graphics::VertexElementType::VEC_3F},
    });

    m_cubeArray->AddVertexBuffer(vertexBuffer);
    m_cubeArray->SetIndexBuffer(indexBuffer);

    m_lightArray->AddVertexBuffer(vertexBuffer);
    m_lightArray->SetIndexBuffer(indexBuffer);

    m_rot = glm::vec4(0);
    m_pos = glm::vec3(0);
    m_lightPos = glm::vec3(0);
    m_lightColor = glm::vec3(0.7f, 0.3f, 0.6f);
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

    m_cubeShader->Bind();
    m_cubeShader->SetInt("texture1", 0);
    m_cubeShader->SetInt("texture2", 1);
    m_mix = 0.2f;
}

ImGuiLayer::~ImGuiLayer()
{}

void ImGuiLayer::OnUpdate()
{
    m_camera.Update();

    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, m_lightPos);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, m_pos);
    model = glm::rotate(model, glm::radians(m_rot.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(m_rot.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(m_rot.z), glm::vec3(0.0f, 0.0f, 1.0f));

    m_texture1->Bind(0);
    m_texture2->Bind(1);

    m_lightShader->Bind();
    m_lightShader->SetVec3f("lightColor", m_lightColor);
    m_lightShader->SetMat4f("modelViewProjection", m_camera.GetViewProjectionMatrix() * lightModel);
    m_lightArray->Bind();
    glDrawElements(GL_TRIANGLES, m_lightArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);

    m_cubeShader->Bind();
    m_cubeShader->SetMat4f("modelViewProjection", m_camera.GetViewProjectionMatrix() * model);
    m_cubeShader->SetMat4f("model", model);
    m_cubeShader->SetMat4f("normalMatrix", glm::transpose(glm::inverse(model)));
    m_cubeShader->SetVec3f("lightPos", m_lightPos);
    m_cubeShader->SetVec3f("lightColor", m_lightColor);
    m_cubeShader->SetVec3f("viewPos", m_camera.GetPosition());
    m_cubeShader->SetFloat("ambientStrength", m_ambientStrength);
    m_cubeShader->SetFloat("specularStrength", m_specularStrength);
    m_cubeShader->SetInt("shininess", m_shininess);
    m_cubeShader->SetFloat("mix_ratio", m_mix);

    m_cubeArray->Bind();
    glDrawElements(GL_TRIANGLES, m_cubeArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
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
    ImGui::SliderFloat("X Cube Position", &m_pos.x, -20.0f, 10.0f);
    ImGui::SliderFloat("Y Cube Position", &m_pos.y, -20.0f, 10.0f);
    ImGui::SliderFloat("Z Cube Position", &m_pos.z, -20.0f, 10.0f);
    ImGui::NewLine();
    ImGui::SliderFloat("Ambient Strength", &m_ambientStrength, 0.0f, 1.0f);
    ImGui::SliderFloat("Specular Strength", &m_specularStrength, 0.0f, 1.0f);
    ImGui::SliderInt("Shininess", &m_shininess, 0, 256);
    ImGui::NewLine();
    ImGui::SliderFloat("X Light Position", &m_lightPos.x, -20.0f, 10.0f);
    ImGui::SliderFloat("Y Light Position", &m_lightPos.y, -20.0f, 10.0f);
    ImGui::SliderFloat("Z Light Position", &m_lightPos.z, -20.0f, 10.0f);
    ImGui::NewLine();
    ImGui::ColorEdit3("clear color", &m_lightColor.r);
    ImGui::NewLine();
    if (ImGui::Button("Reset cube position"))
        m_pos = glm::vec3(0);

    if (ImGui::Button("Reset light position"))
        m_lightPos = glm::vec3(0);

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
        case VOLT_KEY_R:
        {
            m_cubeShader->Reload();
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
