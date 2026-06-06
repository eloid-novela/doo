#include "../include/doo/monitor.hpp"
#include <fstream>
#include <string>

namespace doo 
{
    std::uint64_t monitor::read_bytes(const std::string& path) const
    {
        std::ifstream file(path);
        std::uint64_t bytes{};
        file >> bytes;

        return bytes;
    }

    std::uint64_t monitor::get_total_downloaded_since(const std::string& timestamp) const
    {
        const auto& bytes = read_bytes("/sys/class/net/wlp2s0/statistics/rx_bytes");
        return bytes;
    }

    std::uint64_t monitor::get_total_uploaded_since(const std::string& path) const
    {
        const auto& bytes = read_bytes("/sys/class/net/wlp2s0/statistics/tx_bytes");
        return bytes;
    }

    std::uint64_t monitor::get_total_since(const std::string& timestamp) const 
    {
        const auto& d = get_total_downloaded_since(timestamp);
        const auto& u = get_total_uploaded_since(timestamp);
        return d+u;
    }
}