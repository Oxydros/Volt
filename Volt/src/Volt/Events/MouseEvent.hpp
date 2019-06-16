#pragma once

#include "Volt/Events/Event.hpp"

namespace Volt::Event {


    class MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(double x, double y) : Event(EventType::MOUSE_MOVED), m_x(x), m_y(y) {}
        virtual ~MouseMovedEvent() {}

        inline double GetX() const { return m_x; }
        inline double GetY() const { return m_y; }

    protected:
        double  m_x, m_y;
    };

    class MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(double xOffset, double yOffset)
            : Event(EventType::MOUSE_SCROLLED), m_xOffset(xOffset), m_yOffset(yOffset) {}
        virtual ~MouseScrolledEvent() {}

        inline double GetOffsettX() const { return m_xOffset; }
        inline double GetOffsetY() const { return m_yOffset; }

    protected:
        double  m_xOffset, m_yOffset;
    };

    class MouseButtonEvent : public Event
    {
    public:
        inline int GetButton() const { return m_buttonCode; }

    protected:
        MouseButtonEvent(EventType type, int buttonCode) : Event(type), m_buttonCode(buttonCode) {}
        virtual ~MouseButtonEvent() {}

        int m_buttonCode;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(int buttonCode) : MouseButtonEvent(EventType::MOUSE_BUTTON_PRESSED, buttonCode) {}
        virtual ~MouseButtonPressedEvent() {}
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(int buttonCode) : MouseButtonEvent(EventType::MOUSE_BUTTON_RELEASED, buttonCode) {}
        virtual ~MouseButtonReleasedEvent() {}
    };
}