#pragma once

#include <glm/glm.hpp>

#include "Volt/Layer.hpp"

#include "Volt/Graphics/Shader.hpp"
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

    unsigned int                                        m_vertexArrayObj;
    Volt::Graphics::Shader::ShaderPtr                   m_shader;
    Volt::Graphics::VertexArray::VertexArrayPtr         m_vertexArray;

    glm::vec3                                           m_rot;
    glm::vec3                                           m_pos;

    Volt::World::Camera                                 m_camera;
    bool                                                m_mousePressed;
};
