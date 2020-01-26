#pragma once

// Base class for a loss function
// This class computes the average lost
// with a function

#include "IronMind/types.h"

namespace im
{
    class Tensor;
    
    class Loss
    {
    public:
        Loss(value_t (*loss)(const value_t label, const value_t output),
            value_t (*derivative)(const value_t label, const value_t output));

    public:
        // Computes the loss between the guessed output and the label
        virtual value_t Compare(const Tensor& LABEL, const Tensor& OUTPUT) const;

    public:
        value_t (*loss)(const value_t label, const value_t output);
        value_t (*derivative)(const value_t label, const value_t output);
    };
} // namespace im
