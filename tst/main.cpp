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

    // auto b = Tensor({
    //     16, 8, 4,
    // }, {3});

    // b.WeightedSum(a).ExpandDims().Print();

    // b.Map([](float &v){
    //     --v;
    // }).Print();

    a.Save(".tst_tensor");
    a.Print();

    a = Tensor();
    a.Print();

    a = Tensor::Load(".tst_tensor");
    a.Print();

    return 0;
}
