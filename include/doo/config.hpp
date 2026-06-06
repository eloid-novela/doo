#pragma once

#include <string>

namespace doo
{
struct Config
{
    int limit_gb;
    std::string interface;

    static Config load(const std::string& path);
};
}