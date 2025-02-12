#pragma once

#include "Company.h"
#include <optional>
#include <memory>

namespace ppp::utils
{

class Parser
{
public:
    static std::optional<Company> parseCSV(const std::string& filename);
};

} // namespace ppp::utils
