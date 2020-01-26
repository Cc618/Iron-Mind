#pragma once

// Base class for a layer

#include "IronMind/Tensor.h"

namespace im
{
    class Layer
    {
    public:
        Layer(const shape_t INPUT_SHAPE={}, const shape_t OUTPUT_SHAPE={})
            : inputShape(INPUT_SHAPE), outputShape(OUTPUT_SHAPE)
        {}

    public:
        shape_t InputShape() const;
        shape_t OutputShape() const;

    public:
        // Computes y = f(x) with f this layer
        virtual Tensor operator()(const Tensor &x) const = 0;

    public:
        bool Trainable = true;
    
    protected:
        shape_t inputShape;
        shape_t outputShape;
    };
} // namespace im
