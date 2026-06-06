#include "../include/doo/limiter.hpp"

namespace doo
{
Limiter::Limiter(const Config& config)
    : config_(config)
{
}

bool Limiter::limit_reached()
{

    return false;
}
}