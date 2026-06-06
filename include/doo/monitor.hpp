#pragma once

#include <cstdint>
#include <string>

namespace doo 
{
class monitor 
{   
    public:
        std::uint64_t get_total_downloaded_since(const std::string& timestamp) const;
        std::uint64_t get_total_uploaded_since(const std::string& timestamp) const;
        std::uint64_t get_total_since(const std::string& timestamp) const;

    private:
        std::uint64_t read_bytes(const std::string& path) const;
};
}