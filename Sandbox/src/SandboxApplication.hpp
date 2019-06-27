#pragma once

#include "Volt.hpp"

#include "Volt/Graphics/Shader.hpp"

class SandboxApplication : public Volt::Application,
    public Volt::Event::EventListener<Volt::Event::KeyPressedEvent>,
    public Volt::Event::EventListener<Volt::Event::WindowClosedEvent>,
    public Volt::Event::EventListener<Volt::Event::WindowMovedEvent>,
    public Volt::Event::EventListener<Volt::Event::WindowResizeEvent>
{
public:
    SandboxApplication(int _argc, char **_argv);
    virtual ~SandboxApplication() {}

    bool handleEvent(Volt::Event::KeyPressedEvent const &event) override;
    bool handleEvent(Volt::Event::WindowClosedEvent const &event) override;
    bool handleEvent(Volt::Event::WindowMovedEvent const &event) override;
    bool handleEvent(Volt::Event::WindowResizeEvent const &event) override;

protected:
    void OnUpdate() override;

private:
    unsigned int                        m_vertexBuffer;
    unsigned int                        m_vertexArrayObj;
    unsigned int                        m_indexBuffer;
    Volt::Graphics::Shader::ShaderPtr   m_shader;
};