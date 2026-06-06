#pragma once
#include "config.hpp"

namespace doo
{
class Limiter
{
public:
    explicit Limiter(const Config& config);

    bool limit_reached();

private:
    Config config_;
};
}