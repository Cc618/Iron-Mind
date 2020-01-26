#include "IronMind/Loss.h"
#include "IronMind/Tensor.h"
#include "IronMind/errors.h"

namespace im
{
    Loss *Loss::MSE()
    {
        return new Loss(
            [](value_t a, value_t b){
                const value_t DIFF = a - b;
                return DIFF * DIFF;
            },
            [](value_t a, value_t output){
                return -2 * output;
            }
        );
    }

    Loss::Loss(value_t (*loss)(const value_t label, const value_t output),
        value_t (*derivative)(const value_t label, const value_t output))
        : loss(loss), derivative(derivative)
    {}

    value_t Loss::Compare(const Tensor& LABEL, const Tensor& OUTPUT) const
    {
        Assert(LABEL.shape == OUTPUT.shape, "(Loss::Compare) Both tensors must have the same shape");

        // Add all losses element wise
        value_t sum = 0;
        for (size_t i = 0; i < LABEL.size; ++i)
            sum += loss(LABEL.data[i], OUTPUT.data[i]);
        
        // Compute the average
        return sum / (value_t)LABEL.size;
    }
} // namespace im
