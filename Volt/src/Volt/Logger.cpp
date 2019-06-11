#include "Logger.hpp"

namespace Volt
{
    std::shared_ptr<spdlog::logger>  Logger::VoltLogger = spdlog::stdout_color_mt("volt_logger");
}