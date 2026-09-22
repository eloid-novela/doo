#include "../include/doo/limiter.hpp"

#include <limits>

namespace doo
{
Limiter::Limiter(const Config& config)
    : config_(config), monitor_(config.interface)
{
}

std::uint64_t Limiter::current_usage_bytes() const
{
    return monitor_.get_total_since("");
}

bool Limiter::limit_reached() const
{
    constexpr std::uint64_t gigabyte = 1'000'000'000;
    if (config_.limit_gb > std::numeric_limits<std::uint64_t>::max() / gigabyte)
    {
        return true;
    }
    return current_usage_bytes() >= config_.limit_gb * gigabyte;
}
}