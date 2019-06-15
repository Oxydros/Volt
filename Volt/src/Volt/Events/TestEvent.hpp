#pragma once

#include "Volt/Events/Event.hpp"
#include "Volt/Logger.hpp"

namespace Volt::Event {
    class TestEvent : public Event
    {
    public:
        TestEvent() : Event(EventType::NONE) {}
        virtual ~TestEvent() {}

        void testFunction() const {
            VOLT_INFO("HEY ! Hello from test event function !");
        }
    };
}