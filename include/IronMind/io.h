#pragma once

// IO related functions

#include <string>
#include <vector>

namespace im
{
    // Write or read file
    bool WriteFile(const std::string& PATH, const std::vector<uint8_t>& BYTES);
    std::vector<uint8_t> ReadFile(const std::string& PATH);
} // namespace im
