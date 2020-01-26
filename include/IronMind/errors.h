#pragma once

// To print errors relative to Iron Mind

#include <string>

namespace im
{
    // Stops the program
    void Assert(const bool MUST_BE_TRUE, const std::string& MSG="");
} // namespace im
