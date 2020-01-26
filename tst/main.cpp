#include <iostream>
#include <vector>

#include "IronMind/Tensor.h"
#include "IronMind/types.h"

int main()
{
    using namespace std;
    using namespace im;


    /*
    Batch x = Batch(Tensor({
        0, 0,
        1, 0,
        0, 1,
        1, 1,
    }, {4, 2}));

    Batch y = Batch(Tensor({
        1, 0,
        0, 1,
        0, 1,
        1, 0,
    }, {4, 2}));

    Model model(
        {
            new FullyConnected(4),
            new Activation::Sigmoid(),
            new FullyConnected(2),
            new Activation::Sigmoid(),
        },
        Optimizer::SGD(0.001),
        Loss::MSE(),
        inputSize=2,
        Initializer::Uniform()
    );

    model.Train(x, y, 100);

    model(x);
    */








    // Tensor a = Tensor({
    //     1, 2,
    //     3, 4,
    //     5, 6,
    // }, {3, 2});

    // auto b = Tensor({
    //     16, 8, 4,
    // }, {3});

    // b.WeightedSum(a).ExpandDims().Print();

    // b.Map([](float &v){
    //     --v;
    // }).Print();

    // a.Save(".tst_tensor");
    // a.Print();

    // a = Tensor();
    // a.Print();

    // a = Tensor::Load(".tst_tensor");
    // a.Print();

    return 0;
}
