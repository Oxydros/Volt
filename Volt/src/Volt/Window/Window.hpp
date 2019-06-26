#pragma once

#include <memory>

#include "Volt/Graphics/IContext.hpp"

namespace Volt {

    struct WindowSettings
    {
        int                 Width;
        int                 Height;
        std::string const   &Name;

        WindowSettings(std::string const &name, int width, int height)
            : Name(name), Width(width), Height(height) {}
    };

    class Window
    {
    public:
        typedef std::unique_ptr<Window> WindowPtr;

    public:
        static WindowPtr CreateWindow(WindowSettings const &settings);

    public:
        Window(WindowSettings const &settings) : m_settings(settings) {}
        virtual ~Window() {}

        // -- ImGUI
        //
        //ImGui is dependant of the window for its context creation
        //So we let it leave inside the window object
        
        //Initialize the ImGui context
        virtual void InitializeImGuiContext() = 0;
        //Begin the rendering ImGui content
        virtual void ImGuiBegin() = 0;
        //End the rendering of ImGui content
        virtual void ImGuiEnd() = 0;

        virtual void Clear() = 0;
        virtual void OnUpdate() = 0;
        virtual Volt::Graphics::IContext *GetGraphicContext() = 0;
        virtual void *GetRawWindow() const = 0;

    //--- Retrieve Windows setting ---//
        inline int const &GetHeight() const { return m_settings.Height; }
        inline int const &GetWidth() const { return m_settings.Width; }
        inline std::string const &GetName() const { return m_settings.Name; }
        inline WindowSettings const &GetSettings() const { return m_settings; }

    private:
        WindowSettings  m_settings;
    };

    class WindowCreationException : virtual public std::exception
    {
    public:
        WindowCreationException(std::string const &message) : m_message(message) {}
        virtual ~WindowCreationException() {}

        virtual char const* what() const noexcept { return m_message.c_str(); }
    protected:
        std::string m_message;
    };
}