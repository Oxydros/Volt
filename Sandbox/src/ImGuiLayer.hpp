#pragma once

#include "Volt/Layer.hpp"

//ImGui debug layer for Sandbox application
class ImGuiLayer : public Volt::Layer
{
public:
    ImGuiLayer();
    virtual ~ImGuiLayer();
    void OnUpdate () override;
    void OnImGUI() override;

private:
    bool m_show_demo_window = true;
    bool m_show_another_window = false;
};
