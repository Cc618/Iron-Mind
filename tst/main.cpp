#include <iostream>
#include <vector>

#include "IronMind/Tensor.h"
#include "IronMind/types.h"

int main()
{
    using namespace std;
    using namespace im;

    Tensor a = Tensor({
        1, 2,
        3, 4,
        5, 6,
    }, {3, 2});

    Tensor b = a;
    
    a[{1, 1}] = -1;

    a.Print();
    b.Print();

    return 0;
}
