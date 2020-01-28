#include "IronMind/Activation.h"
#include <cmath>

namespace im
{
    Activation Activation::Linear()
    {
        return Activation([](value_t &val){}, [](value_t &val){ val = 1; });
    }

    Activation Activation::Relu()
    {
        return Activation(
            [](value_t &val){
                if (val < 0)
                    val = 0;
            },
            [](value_t &val){
                if (val <= 0)
                    val = 0;
                else
                    val = 1;
            }
        );
    }

    Activation Activation::Sigmoid()
    {
        return Activation(
            [](value_t &x){
                x = 1.f / (1 + expf(-x));
            },
            [](value_t &x){
                const size_t ex = expf(-x);
                x = ex / ((1 + ex) * (1 + ex));
            }
        );
    }

    Activation::Activation(void (*function)(float &val), void (*derivative)(float &val))
        : function(function), derivative(derivative)
    {}

    void Activation::InitOptimization(History &inputs, History &gradients) const
    {
        inputs.Push(Tensor(inputShape));
        gradients.Push(Tensor(outputShape));
    }

    Tensor Activation::operator()(const Tensor &x) const
    {
        return Tensor(x).Map(function);
    }
} // namespace im
