#pragma once

#include <cstdint>

namespace Volt::Event {

    enum class EventType : uint8_t {
        NONE = 0,
        //Windows events
        WINDOW_CLOSED, WINDOW_RESIZED, WINDOW_MOVED,
        //Mouse events
        MOUSE_BUTTON_PRESSED, MOUSE_BUTTON_RELEASED, MOUSE_MOVED, MOUSE_SCROLLED,
        //Keyboard events,
        KEY_PRESSED, KEY_RELEASED, KEY_REPEAT, KEY_TYPED
    };

    class Event
    {
    public:
        Event(EventType type) : m_type(type), m_handled(false) {}
        virtual ~Event() {}

        inline void handle() { m_handled = true; }
        inline bool IsHandled() const { return m_handled; }
        inline EventType GetType() const { return m_type; }

    private:
        bool        m_handled;
        EventType   m_type;  
    };

    template<class EventMsgType>
    class EventListener
    {
    public:
        EventListener() { Attach(); }
        virtual ~EventListener(){ Detach(); }

        void Attach()
        {
            _handlers.push_back(this);
        }

        void Detach()
        {
            auto it = std::find(_handlers.begin(), _handlers.end(), this);
            if (it != _handlers.end()) {
                _handlers.erase(it);
            }
        }

        virtual bool handleEvent(EventMsgType const &event) = 0;

    private:
        typedef EventListener<EventMsgType>* Handler;
        static std::vector<Handler> _handlers;

        static inline std::vector<Handler> GetHandlers() { return _handlers; }

    public:
        static void Deliver(EventMsgType const &event){
            for (auto &handler : GetHandlers())
            {
                //If event handled
                if (handler->handleEvent(event))
                    break;
            }
        }
    };

    template<class EventMsgType>
    void DispatchEvent(EventMsgType const &event) {
        Volt::Event::EventListener<EventMsgType>::Deliver(event);
    }

    template<class EventMsgType>
    std::vector<EventListener<EventMsgType>*> EventListener<EventMsgType>::_handlers;
}