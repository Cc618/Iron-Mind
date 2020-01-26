#pragma once

// A model is a layer with optimizer
// and loss, it can be trained

#include "IronMind/Layer.h"

namespace im
{
    class Model : public Layer
    {
    public:
        Model(Layer *content);
        ~Model();

        // TODO : Rule of 3

    public:
        // Predicts the output
        virtual Tensor operator()(const Tensor &x) const override;

    private:
        Layer *content;
    };
} // namespace im
