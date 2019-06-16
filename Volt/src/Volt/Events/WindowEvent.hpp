#pragma once

#include "Volt/Events/Event.hpp"

namespace Volt::Event {

    class WindowClosedEvent : public Event
    {
    public:
        WindowClosedEvent() : Event(EventType::WINDOW_CLOSED) {}
        virtual ~WindowClosedEvent() {}
    };

    class WindowMovedEvent : public Event
    {
    public:
        WindowMovedEvent(double x, double y)
            : Event(EventType::WINDOW_MOVED), m_x(x), m_y(y) {}
        virtual ~WindowMovedEvent() {}

        inline double GetX() const { return m_x; }
        inline double GetY() const { return m_y; }

    protected:
        double  m_x, m_y;
    };

    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(int width, int height)
            : Event(EventType::WINDOW_RESIZED), m_width(width), m_height(height) {}
        virtual ~WindowResizeEvent() {}

        inline int GetWidth() const { return m_width; }
        inline int GetHeight() const { return m_height; }

    protected:
        int m_width, m_height;
    };
}