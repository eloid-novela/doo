#include "../include/doo/limiter.hpp"

#include <format>
#include <limits>
#include <iostream>
#include <chrono>

namespace doo
{
Limiter::Limiter(const Config& config)
    : config_(config), monitor_(config.interface)
{
}

std::uint64_t Limiter::current_usage_bytes() const
{
    auto now = std::chrono::system_clock::now();
    now = std::chrono::zoned_time{"Africa/Maputo", now};
    std::cout << std::format("{:%d-%m-%Y %H:%M:%S}", now) << std::endl;
    return monitor_.get_total_since(std::format("{:%d-%m-%Y %H:%M:%S}", now));
}

bool Limiter::limit_reached() const
{

    constexpr std::uint64_t gigabyte = 1'000'000'000;
    if (config_.limit_gb > std::numeric_limits<std::float_t>::max() / gigabyte)
    {
        return true;
    }

    std::cout << current_usage_bytes() << " [>=] " << config_.limit_gb * gigabyte << std::endl;
    return current_usage_bytes() >= config_.limit_gb * gigabyte;
}
}