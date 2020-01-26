#include "IronMind/errors.h"
#include <iostream>
#include "assert.h"

namespace im
{
    // Stops the program
    void Assert(const bool MUST_BE_TRUE, const std::string& MSG)
    {
        if (!MUST_BE_TRUE)
            std::cerr << "Iron Mind assert failed : " << MSG << std::endl;

        assert(MUST_BE_TRUE);
    }
} // namespace im
