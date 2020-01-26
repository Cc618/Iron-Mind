#include "IronMind/Activation.h"
#include <cmath>

namespace im
{
    Activation Activation::linear()
    {
        return Activation([](value_t &val){}, [](value_t &val){ val = 1; });
    }

    Activation Activation::relu()
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

    Activation Activation::sigmoid()
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

    Tensor Activation::operator()(const Tensor &x) const
    {
        return Tensor(x).Map(function);
    }
} // namespace im
