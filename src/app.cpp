#include "../include/doo/app.hpp"
#include "../include/doo/logger.hpp"
#include "../include/doo/config.hpp"
#include "../include/doo/limiter.hpp"
#include "../include/doo/network_controller.hpp"

#include <chrono>
#include <thread>
#include <string>
#include <stdexcept>

namespace doo
{
int app::run(int argc, char** argv)
{
    Logger::info("Starting Doo...");

    std::string config_path = "configs/doo.json";
    bool once = false;
    for (int index = 1; index < argc; ++index)
    {
        const std::string argument = argv[index];
        if (argument == "--once")
        {
            once = true;
        }
        else if (argument == "--config" && index + 1 < argc)
        {
            config_path = argv[++index];
        }
        else if (argument == "--help")
        {
            Logger::info("Usage: doo [--config PATH] [--once]");
            return 0;
        }
        else
        {
            throw std::runtime_error("Unknown argument: " + argument);
        }
    }

    const Config config = Config::load(config_path);

    Limiter limiter(config);
    NetworkController net;

    do
    {
        Logger::info("Checking data usage...");
        if (limiter.limit_reached())
        {
            Logger::warn("Data limit reached. Disabling network...");
            net.disable();
            return 2;
        }

        Logger::info("Usage is within the configured limit.");
        if (!once)
        {
            std::this_thread::sleep_for(std::chrono::seconds(config.poll_interval_seconds));
        }
    } while (!once);

    return 0;
}
}