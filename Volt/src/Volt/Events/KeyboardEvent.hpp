#pragma once

#include "Volt/Events/Event.hpp"

namespace Volt::Event {

    class KeyboardEvent : public Event
    {

    public:
        inline int GetKeyCode() const { return m_keyCode; }

    protected:
        KeyboardEvent(EventType type, int keyCode) : Event(type), m_keyCode(keyCode) {}
        virtual ~KeyboardEvent() {}

        int m_keyCode;
    };

    class KeyPressedEvent : public KeyboardEvent
    {
    public:
        KeyPressedEvent(int keyCode, bool repeat = false)
            : KeyboardEvent(EventType::KEY_PRESSED, keyCode), m_repeat(repeat) {}
        virtual ~KeyPressedEvent() {}

        bool IsRepeat() const { return m_repeat; }

    protected:
        bool    m_repeat;
    };

    class KeyReleasedEvent : public KeyboardEvent
    {
    public:
        KeyReleasedEvent(int keyCode) : KeyboardEvent(EventType::KEY_RELEASED, keyCode) {}
        virtual ~KeyReleasedEvent() {}
    };

    class KeyTypedEvent : public KeyboardEvent
    {
    public:
        KeyTypedEvent(int keyCode) : KeyboardEvent(EventType::KEY_TYPED, keyCode) {}
        virtual ~KeyTypedEvent() {}
    };
}