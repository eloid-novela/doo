#include "../include/doo/config.hpp"

#include <fstream>
#include <regex>
#include <sstream>
#include <stdexcept>

namespace doo
{
namespace
{
std::string read_file(const std::string& path)
{
    std::ifstream file(path);
    if (!file)
    {
        throw std::runtime_error("Cannot open configuration file: " + path);
    }

    std::ostringstream content;
    content << file.rdbuf();
    return content.str();
}

std::string read_string(const std::string& json, const std::string& key)
{
    const std::regex expression("\\\"" + key + "\\\"\\s*:\\s*\\\"([^\\\"]+)\\\"");
    std::smatch match;
    if (!std::regex_search(json, match, expression))
    {
        throw std::runtime_error("Missing configuration field: " + key);
    }
    return match[1].str();
}

std::uint64_t read_number(const std::string& json, const std::string& key)
{
    const std::regex expression("\\\"" + key + "\\\"\\s*:\\s*([0-9]+)");
    std::smatch match;
    if (!std::regex_search(json, match, expression))
    {
        throw std::runtime_error("Missing configuration field: " + key);
    }
    return std::stoull(match[1].str());
}
}

Config Config::load(const std::string& path)
{
    const auto json = read_file(path);
    Config config{
        .limit_gb = read_number(json, "limit_gb"),
        .period = read_string(json, "period"),
        .interface = read_string(json, "interface"),
        .poll_interval_seconds = static_cast<std::uint32_t>(read_number(json, "poll_interval_seconds"))
    };

    if (config.limit_gb == 0 || config.poll_interval_seconds == 0)
    {
        throw std::runtime_error("limit_gb and poll_interval_seconds must be greater than zero");
    }
    if (config.period != "daily" && config.period != "weekly" && config.period != "monthly")
    {
        throw std::runtime_error("period must be daily, weekly, or monthly");
    }
    if (config.interface.empty())
    {
        throw std::runtime_error("interface must not be empty");
    }

    return config;
}
}