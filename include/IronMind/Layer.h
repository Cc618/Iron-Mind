#pragma once

// Base class for a layer

#include "IronMind/Tensor.h"
#include "IronMind/History.h"

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
        // Adds the tensors for the optimizer
        virtual void InitOptimization(History &inputs, History &gradients) const = 0;
        // Computes all partial derivatives of
        // the loss wrt each weight of the layer
        virtual void ComputeGradients(const Tensor &INPUT, const Tensor &PREV_PROPAGATION_GRADIENT, History &gradients) const {}
        // Returns the partial derivatives of
        // the loss wrt to the outputs of
        // this layer
        virtual Tensor ComputePropagationGradient(const Tensor &INPUT, const Tensor &PREV_PROPAGATION_GRADIENT) const = 0;

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
