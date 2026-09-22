#include "../include/doo/monitor.hpp"
#include <fstream>
#include <stdexcept>
#include <string>
#include <utility>

namespace doo 
{
    monitor::monitor(std::string interface_name)
        : interface_(std::move(interface_name))
    {
    }

    std::uint64_t monitor::read_bytes(const std::string& path) const
    {
        std::ifstream file(path);
        if (!file)
        {
            throw std::runtime_error("Cannot read network statistics: " + path);
        }
        std::uint64_t bytes{};
        file >> bytes;

        return bytes;
    }

    std::uint64_t monitor::get_total_downloaded_since(const std::string& timestamp) const
    {
        (void)timestamp;
        const auto bytes = read_bytes("/sys/class/net/" + interface_ + "/statistics/rx_bytes");
        return bytes;
    }

    std::uint64_t monitor::get_total_uploaded_since(const std::string& timestamp) const
    {
        (void)timestamp;
        const auto bytes = read_bytes("/sys/class/net/" + interface_ + "/statistics/tx_bytes");
        return bytes;
    }

    std::uint64_t monitor::get_total_since(const std::string& timestamp) const 
    {
        const auto d = get_total_downloaded_since(timestamp);
        const auto u = get_total_uploaded_since(timestamp);
        return d+u;
    }
}