#include "IronMind/Initializer.h"
#include <chrono>
#include "IronMind/Tensor.h"

namespace im
{
    uint_fast32_t Initializer::Seed = std::chrono::system_clock::now().time_since_epoch().count();

    UniformDistribution::UniformDistribution(const value_t a, const value_t b)
        : dis(a, b)
    {}

    value_t UniformDistribution::Next(std::default_random_engine& gen)
    {
        return dis(gen);
    }
    
    NormalDistribution::NormalDistribution(const value_t MEAN, const value_t STDDEV)
        : dis(MEAN, STDDEV)
    {}

    value_t NormalDistribution::Next(std::default_random_engine& gen)
    {
        return dis(gen);
    }

    Initializer Initializer::Uniform(const value_t a, const value_t b)
    {
        return Initializer(new UniformDistribution(a, b));
    }

    Initializer Initializer::Normal(const value_t MEAN, const value_t STDDEV)
    {
        return Initializer(new NormalDistribution(MEAN, STDDEV));
    }

    Initializer::Initializer(Distribution *dis)
        : dis(dis), generator(Seed)
    {}
    
    Initializer::~Initializer()
    {
        delete dis;
    }

    void Initializer::Init(Tensor& data)
    {
        for (size_t i = 0; i < data.size; ++i)
            // Access raw data
            data.data[i] = dis->Next(generator);
    }
}
