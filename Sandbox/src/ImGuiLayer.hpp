#pragma once

#include <glm/glm.hpp>

#include "Volt/Layer.hpp"

#include "Volt/Graphics/Shader.hpp"
#include "Volt/Graphics/Texture.hpp"
#include "Volt/Graphics/Buffers.hpp"

#include "Volt/World/Camera.hpp"
#include "Volt/Event.hpp"

//ImGui debug layer for Sandbox application
class ImGuiLayer :  public Volt::Layer,
                    public Volt::Event::EventListener<Volt::Event::KeyPressedEvent>,
                    public Volt::Event::EventListener<Volt::Event::MouseMovedEvent>,
                    public Volt::Event::EventListener<Volt::Event::MouseButtonPressedEvent>,
                    public Volt::Event::EventListener<Volt::Event::MouseButtonReleasedEvent>
{
public:
    ImGuiLayer();
    virtual ~ImGuiLayer();
    void OnUpdate () override;
    void OnImGUI() override;

    bool handleEvent(Volt::Event::KeyPressedEvent const &event) override;
    bool handleEvent(Volt::Event::MouseMovedEvent const &event) override;
    bool handleEvent(Volt::Event::MouseButtonPressedEvent const &event) override;
    bool handleEvent(Volt::Event::MouseButtonReleasedEvent const &event) override;

private:
    bool m_show_demo_window = true;
    bool m_show_another_window = false;

    float                                               m_mix;

    Volt::Graphics::Texture::TexturePtr                 m_texture1;
    Volt::Graphics::Texture::TexturePtr                 m_texture2;

    Volt::Graphics::Shader::ShaderPtr                   m_cubeShader;
    Volt::Graphics::Shader::ShaderPtr                   m_lightShader;

    Volt::Graphics::VertexArray::VertexArrayPtr         m_cubeArray;
    Volt::Graphics::VertexArray::VertexArrayPtr         m_lightArray;

    glm::vec3                                           m_lightPos;
    glm::vec3                                           m_lightColor;
    glm::vec3                                           m_rot;
    glm::vec3                                           m_pos;

    float                                               m_ambientStrength = 0.1;
    float                                               m_specularStrength = 0.5;
    int                                                 m_shininess = 256;

    Volt::World::PerspectiveCamera                      m_camera;
    bool                                                m_mousePressed;
};
