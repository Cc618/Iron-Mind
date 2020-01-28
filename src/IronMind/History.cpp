#include "IronMind/History.h"

namespace im
{
    void History::Push(const Tensor& PLACEHOLDER)
    {
        tensors.push_back(PLACEHOLDER);
    }

    Tensor &History::Next()
    {
        if (forward)
            return tensors[current++];
        else
            return tensors[current--];
    }

    void History::Reset()
    {
        for (Tensor &t : tensors)
            t.Zero();
    }

    void History::SetForward(const bool FORWARD)
    {
        forward = FORWARD;

        if (FORWARD)
            current = 0;
        else
            current = tensors.size() - 1;
    }
} // namespace im
