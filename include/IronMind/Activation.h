#pragma once

// An activation layer, applies a function
// on the input

#include "IronMind/Layer.h"

namespace im
{
    class Activation : public Layer
    {
    public:
        // Static constructors
        static Activation Linear();
        static Activation Relu();
        static Activation Sigmoid();

    public:
        Activation(void (*function)(value_t &val), void (*derivative)(value_t &val));

    public:
        virtual void InitOptimization(History &inputs, History &gradients) const override;

    public:
        // Computes y = f(x) with f this layer
        virtual Tensor operator()(const Tensor &x) const override;

    private:
        void (*function)(value_t &val);
        void (*derivative)(value_t &val);
    };
} // namespace im
