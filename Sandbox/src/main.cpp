#include "Volt.hpp"

class SandboxApplication : public Volt::Application
{
public:
    SandboxApplication(int _argc, char **_argv) : Volt::Application(_argc, _argv)
    {
        VOLT_INFO("Launching Sandbox...");
    }
    virtual ~SandboxApplication() {}
};

PROGRAM_APPLICATION(SandboxApplication)