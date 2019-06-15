#pragma once

#include "Volt/Logger.hpp"

namespace Volt {

    // Logic instance of our program
    class Application
    {
    public:

        Application(int _argc, char **_argv) {}
        virtual ~Application() {}

    public:
        virtual int Run() = 0;
    };

    Application *CreateApplication(int argc, char **argv);
}

// Entry point
int main (int argc, char **argv)
{
    Volt::Logger::Initialize();
    Volt::Application *app = Volt::CreateApplication(argc, argv);
    int ret = app->Run();
    delete app;
    return ret;
}