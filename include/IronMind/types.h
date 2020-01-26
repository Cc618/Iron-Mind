#pragma once

// Types and typedefs

#include <vector>
#include <inttypes.h>

namespace im
{
    // The type of values within tensors
    typedef float value_t;
    typedef std::vector<value_t> value_list_t;

    // To define shapes sizes
    typedef uint64_t shape_size_t;
    typedef std::vector<shape_size_t> shape_t;
} // namespace im
