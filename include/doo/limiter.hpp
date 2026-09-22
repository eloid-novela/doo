#pragma once
#include "config.hpp"
#include "monitor.hpp"

namespace doo
{
class Limiter
{
public:
    explicit Limiter(const Config& config);

    bool limit_reached() const;
    std::uint64_t current_usage_bytes() const;

private:
    Config config_;
    monitor monitor_;
};
}