#pragma once

#include <cstdint>
#include <string>

namespace doo
{
struct Config
{
    std::uint64_t limit_gb;
    std::string period;
    std::string interface;
    std::uint32_t poll_interval_seconds;

    static Config load(const std::string& path);
};
}