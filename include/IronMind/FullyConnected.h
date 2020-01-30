#pragma once

// A layer with all inputs connected
// to weights and biases
// The input must be one dimensional

#include "IronMind/Layer.h"
#include "IronMind/Tensor.h"
#include "IronMind/Initializer.h"

namespace im
{
    class FullyConnected : public Layer
    {
    public:
        FullyConnected(const size_t INPUT_SIZE, const size_t OUTPUT_SIZE, Initializer &init);

    public:
        virtual void InitOptimization(History &inputs, History &gradients) const override;
        
        virtual void ComputeGradients(const Tensor &INPUT, const Tensor &PREV_PROPAGATION_GRADIENT, History &gradients) const override;
        
        virtual Tensor ComputePropagationGradient(const Tensor &INPUT, const Tensor &PREV_PROPAGATION_GRADIENT) const override;

    public:
        // Computes y = f(x) with f this layer
        virtual Tensor operator()(const Tensor &x) const override;

    private:
        Tensor weights;
        Tensor bias;
    };
} // namespace im
