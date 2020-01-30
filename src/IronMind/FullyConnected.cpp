#include "IronMind/FullyConnected.h"

namespace im
{
    FullyConnected::FullyConnected(const size_t INPUT_SIZE, const size_t OUTPUT_SIZE, Initializer &init)
        : Layer({INPUT_SIZE}, {OUTPUT_SIZE}), weights(Tensor::Values({INPUT_SIZE, OUTPUT_SIZE})), bias(Tensor::Values({OUTPUT_SIZE}))
    {
        init.Init(weights);
        init.Init(bias);
    }

    void FullyConnected::InitOptimization(History &inputs, History &gradients) const
    {
        inputs.Push(Tensor::Values({inputShape}));

        // Weights
        gradients.Push(Tensor::Values(weights.Shape()));
        // Bias
        gradients.Push(Tensor::Values(outputShape));
    }

    void FullyConnected::ComputeGradients(const Tensor &y, const Tensor &PREV_PROPAGATION_GRADIENT, History &gradients) const
    {

    }

    Tensor FullyConnected::ComputePropagationGradient(const Tensor &y, const Tensor &PREV_PROPAGATION_GRADIENT) const
    {
        // TODO : Propagation gradient
        return Tensor::Values({inputShape}, 1).WeightedSum(weights, true);
    }

    Tensor FullyConnected::operator()(const Tensor &x) const
    {
        return x.WeightedSum(weights) + bias;
    }
} // namespace im
