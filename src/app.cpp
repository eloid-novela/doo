#include "../include/doo/app.hpp"
#include "../include/doo/logger.hpp"
#include "../include/doo/config.hpp"
#include "../include/doo/limiter.hpp"
#include "../include/doo/network_controller.hpp"

namespace doo
{
int app::run(int argc, char** argv)
{
    Logger::info("Starting Doo...");

    Config config = Config::load("configs/doo.json");

    Limiter limiter(config);
    NetworkController net;

    Logger::info("Checking data usage...");

    if (limiter.limit_reached())
    {
        Logger::warn("Data limit reached! Disabling network...");
        net.disable();
        return 2;
    }

    Logger::info("All good. You are within limit.");
    return 0;
}
}