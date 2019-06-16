#pragma once

namespace Volt::Graphics
{
    class IContext
    {
    public:
        IContext() {}
        virtual ~IContext() {}

    public:
        virtual bool Initialize() = 0;
        virtual void SwapBuffers() = 0;
    };
}

namespace Volt
{
    class ContextCreationException : virtual public std::exception
    {
    public:
        ContextCreationException(std::string const &message) : m_message(message) {}
        virtual ~ContextCreationException() {}

        virtual char const* what() const noexcept { return m_message.c_str(); }
    protected:
        std::string m_message;
    };
}