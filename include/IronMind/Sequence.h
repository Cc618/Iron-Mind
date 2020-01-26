#pragma once

// A sequence gathers multiple layers

#include "IronMind/Layer.h"
#include <vector>

namespace im
{
    class Sequence : public Layer
    {
    public:
        Sequence(std::vector<Layer*>& layers);
        Sequence(const Sequence&) = delete;
        ~Sequence();

        // TODO : Rule of 3
    public:
        // Computes y = f(x) with f this layer
        virtual Tensor operator()(const Tensor &x) const override;
        Sequence &operator=(const Sequence&) = delete;

    private:
        std::vector<Layer*> layers;
    };
} // namespace im
