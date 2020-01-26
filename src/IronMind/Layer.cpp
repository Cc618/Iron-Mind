#include "IronMind/Layer.h"

namespace im
{
    shape_t Layer::InputShape() const
    {
        return inputShape;
    }

    shape_t Layer::OutputShape() const
    {
        return outputShape;
    }
} // namespace im
