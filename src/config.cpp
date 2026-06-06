#include "../include/doo/config.hpp"

namespace doo
{
Config Config::load(const std::string&)
{
    // MVP hardcoded config (depois vamos ler JSON)
    return Config{
        .limit_gb = 5,
        .interface = "wlan0"
    };
}
}