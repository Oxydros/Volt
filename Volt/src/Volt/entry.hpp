#pragma once

#include "Volt/Application.hpp"

// Entry point
int main (int argc, char **argv)
{
    Volt::Logger::Initialize();
    Volt::Application *app = Volt::CreateApplication(argc, argv);
    app->Run();
    delete app;
    return 0;
}