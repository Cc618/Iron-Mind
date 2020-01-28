#pragma once

// Used to handle tensors
// like in a stack

#include <vector>
#include "IronMind/Tensor.h"

namespace im
{
    class History
    {
    public:
        // Adds a tensor
        void Push(const Tensor& PLACEHOLDER);
        // Gives the next tensor (at index current)
        Tensor &Next();
        // Reset tensors to null tensors
        void Reset();
        // The current tensor is either the
        // first one if FORWARD or the last
        // one otherwise
        void SetForward(const bool FORWARD);

    private:
        std::vector<Tensor> tensors;

        // Current tensor index
        size_t current;

        // Whether we increase current with next
        bool forward = true;
    };
} // namespace im
