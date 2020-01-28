#pragma once

// To handle gradients and
// minimize a function

#include "IronMind/Tensor.h"
#include "IronMind/History.h"
#include "IronMind/Layer.h"

namespace im
{
    class Optimizer
    {
    public:
        // Inits all inputs and gradients
        // for this layer and its children
        void Init(const Layer& l);

        // Applies all gradients
        // to this layer and its children
        void ApplyGradient(Layer& l);

    private:
        History inputs;
        History gradients;
    };
} // namespace im
