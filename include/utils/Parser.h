#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <optional>
#include <tuple>
#include <type_traits>

namespace ppp::utils
{

class Parser
{
public:

template <typename T>
static T convert(const std::string &str)
{
    if constexpr (std::is_same_v<T, int>)
    {
        return std::stoi(str);
    }
    else if constexpr (std::is_same_v<T, float>)
    {
        return std::stof(str);
    }
    else 
    {
        return str;
    }
}

template <typename T, typename... Rest>
static std::tuple<T, Rest...> parseTokens(const std::vector<std::string> &tokens, size_t idx) {
    if constexpr (sizeof...(Rest) == 0) {
        return std::make_tuple(convert<T>(tokens[idx]));
    } else {
        return std::tuple_cat(
            std::make_tuple(convert<T>(tokens[idx])),
            parseTokens<Rest...>(tokens, idx + 1)
        );
    }
}

template <typename... Args>
static std::optional<std::tuple<Args...>>
parseLine(const std::string &line) {
    std::vector<std::string> tokens;
    std::istringstream stream(line);
    std::string token;

    while (std::getline(stream, token, ',')) {
        tokens.push_back(token);
    }

    if (tokens.size() != sizeof...(Args)) {
        return std::nullopt;
    }

    return parseTokens<Args...>(tokens, 0);
}

template <typename... Args>
static std::vector<std::tuple<Args...>> parseCSV(const std::string &filename) {
    std::ifstream file(filename);
    std::vector<std::tuple<Args...>> result;
    std::string line;

    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return result;
    }

    if (!std::getline(file, line))
    {
        std::cerr << "Error reading header line from file: " << filename << std::endl;
        return result;
    }
    

    while (std::getline(file, line)) {
        if (auto parsed = parseLine<Args...>(line)) {
            result.push_back(*parsed);
        } else {
            std::cerr << "Failed to parse line: " << line << std::endl;
        }
    }
    return result;
}


};

} // namespace ppp::utils
