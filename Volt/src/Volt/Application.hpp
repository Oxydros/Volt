#pragma once

#include "Volt/Logger.hpp"

namespace Volt {

    // Logic instance of our program
    class Application
    {
    public:

        Application(int _argc, char **_argv) {}
        virtual ~Application() {}

        int Run()
        {
            VOLT_INFO("RUNNING APP");
            return 0;
        }
    };
}

#define PROGRAM_APPLICATION(ApplicationClass)   \
    int main (int argc, char **argv)            \
    {                                           \
        Volt::Logger::Initialize();             \
        ApplicationClass app(argc, argv);       \
        return app.Run();                       \
    }