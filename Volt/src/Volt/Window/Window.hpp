#pragma once

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

        virtual void onUpdate() = 0;
        virtual Volt::Graphics::IContext *getGraphicContext() = 0;

    //--- Retrieve Windows setting ---//
        inline int const &getHeight() const { return m_settings.Height; }
        inline int const &getWidth() const { return m_settings.Width; }
        inline std::string const &getName() const { return m_settings.Name; }
        inline WindowSettings const &getSettings() const { return m_settings; }

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