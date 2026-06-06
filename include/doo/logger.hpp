#pragma once
#include <iostream>

namespace doo
{
class Logger
{
public:
    static void info(const std::string& msg)
    {
        std::cout << "[INFO] " << msg << '\n';
    }

    static void warn(const std::string& msg)
    {
        std::cout << "[WARN] " << msg << '\n';
    }

    static void error(const std::string& msg)
    {
        std::cerr << "[ERROR] " << msg << '\n';
    }
};
}