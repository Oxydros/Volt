#include "Volt.hpp"

class SandboxApplication : public Volt::Application, public Volt::Event::EventListener<Volt::Event::TestEvent>
{
public:
    SandboxApplication(int _argc, char **_argv) : Volt::Application(_argc, _argv)
    {
        VOLT_INFO("Launching Sandbox...");
    }
    virtual ~SandboxApplication() {}

    int Run() override
    {
        VOLT_INFO("Running...");
        Volt::Event::TestEvent test;
        Volt::Event::DispatchEvent(test);
        return 0;
    }

    bool handleEvent(Volt::Event::TestEvent const &event) override
    {
        event.testFunction();
        return false;
    }
};

Volt::Application *Volt::CreateApplication(int argc, char **argv)
{
    return new SandboxApplication(argc, argv);
}