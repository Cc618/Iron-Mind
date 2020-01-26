#include "IronMind/Model.h"

namespace im
{
    Model::Model(Layer *content)
        : Layer(content->InputShape(), content->OutputShape()), content(content)
    {}

    Model::~Model()
    {
        delete content;
    }

    Tensor Model::operator()(const Tensor &x) const
    {
        // Call the content layer
        return (*content)(x);
    }

} // namespace im
