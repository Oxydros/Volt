#include "Volt/ImGui/GLFW/ImGuiContext.hpp"
#include "Volt/Window/Window.hpp"

// -- ImGui
#include "imgui.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

namespace Volt::GLFW::GUI
{
    ImGuiContext::ImGuiContext(Volt::Window *window)
        : m_window(window)
    {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
        //io.ConfigViewportsNoAutoMerge = true;
        //io.ConfigViewportsNoTaskBarIcon = true;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        // Setup Platform/Renderer bindings
        ImGui_ImplGlfw_InitForOpenGL((GLFWwindow *)window->GetRawWindow(), true);
        ImGui_ImplOpenGL3_Init();
    }

    ImGuiContext::~ImGuiContext()
    {
        // -- Cleanup ImGui context
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiContext::BeginDraw()
    {
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiContext::EndDraw()
    {
        ImGuiIO& io = ImGui::GetIO();

	    // io.DisplaySize = ImVec2((float)m_window->GetWidth(), (float)m_window->GetHeight());

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize((GLFWwindow *)m_window->GetRawWindow(), &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    	
        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }
}


//--Creation of window routine
Volt::GUI::ImGuiContext::ImGuiPtr Volt::GUI::ImGuiContext::CreateContext(Volt::Window *window)
{
    return std::make_unique<Volt::GLFW::GUI::ImGuiContext>(window);
}