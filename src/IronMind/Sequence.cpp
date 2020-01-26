#include "IronMind/Sequence.h"
#include "IronMind/errors.h"

namespace im
{
    using namespace std;

    Sequence::Sequence(vector<Layer*>& layers)
        : layers(layers)
    {
        Assert(!layers.empty(), "(Sequence::Sequence) The layers can't be empty");

        inputShape = layers[0]->InputShape();
        shape_t lastOutputShape = layers[0]->OutputShape();

        // Verify whether the layers are connected by their shapes
        for (size_t i = 1; i < layers.size(); ++i)
        {
            Assert(layers[i]->InputShape() == lastOutputShape, std::string("(Sequence::Sequence) The input shape of the layer ") +
                std::to_string(i + 1) + " doesn't match the output shape of the previous layer");
            lastOutputShape = layers[i]->OutputShape();
        }
    }

    Sequence::~Sequence()
    {
        // Free all layers
        for (auto layer : layers)
            delete layer;
    }

    Tensor Sequence::operator()(const Tensor &x) const
    {
        Tensor result = x;

        // Propagate the outputs
        for (auto layer : layers)
            result = (*layer)(result);
        
        return result;
    }
} // namespace im
