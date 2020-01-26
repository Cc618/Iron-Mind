#pragma once

// Base class for a layer

#include "IronMind/Tensor.h"

namespace im
{
    class Layer
    {
    public:
        // Computes y = f(x) with f this layer
        virtual Tensor operator()(const Tensor &x) const = 0;

    public:
        bool Trainable = true;
    };
} // namespace im
