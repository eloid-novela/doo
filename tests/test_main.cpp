#include "doo/config.hpp"

#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>

int main()
{
    const auto path = std::filesystem::temp_directory_path() / "doo-test-config.json";
    {
        std::ofstream file(path);
        file << R"({"limit_gb": 5, "period": "monthly", "interface": "lo", "poll_interval_seconds": 10})";
    }

    const auto config = doo::Config::load(path.string());
    assert(config.limit_gb == 5);
    assert(config.period == "monthly");
    assert(config.interface == "lo");
    assert(config.poll_interval_seconds == 10);

    std::filesystem::remove(path);
    std::cout << "All tests passed\n";
}