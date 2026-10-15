#pragma once

#include <cmath>
#include <cstdint>
#include <string>

namespace doo
{
struct Config
{
    std::float_t limit_gb;
    std::string period;
    std::string interface;
    std::uint32_t poll_interval_seconds;

    static Config load(const std::string& path);
};
}