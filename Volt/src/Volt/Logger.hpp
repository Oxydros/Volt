#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Volt {

    class Logger
    {
    public:

        static void Initialize()
        {
            #ifdef VOLT_DEBUG
                VoltLogger->set_level(spdlog::level::debug);
            #else
                VoltLogger->set_level(spdlog::level::info);
            #endif
        }

        inline static auto& GetLogger() { return VoltLogger; }

    private:
        static std::shared_ptr<spdlog::logger> VoltLogger;
    };
}

#define VOLT_INFO(...)  (Volt::Logger::GetLogger()->info(__VA_ARGS__))
#define VOLT_DEB(...)  (Volt::Logger::GetLogger()->debug(__VA_ARGS__))
#define VOLT_TRACE(...)  (Volt::Logger::GetLogger()->trace(__VA_ARGS__))
#define VOLT_WARN(...)  (Volt::Logger::GetLogger()->warn(__VA_ARGS__))
#define VOLT_ERROR(...)  (Volt::Logger::GetLogger()->error(__VA_ARGS__))
#define VOLT_FATAL(...)  (Volt::Logger::GetLogger()->fatal(__VA_ARGS__))