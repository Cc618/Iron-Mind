#pragma once

// An initializer initializes weights
// of the layers

#include <random>
#include "IronMind/types.h"

namespace im
{
    class Tensor;

    // Random distribution
    class Distribution
    {
    public:
        virtual value_t Next(std::default_random_engine& gen) = 0;
    };

    // Uniform from a to b
    class UniformDistribution : public Distribution
    {
    public:
        UniformDistribution(const value_t a, const value_t b);

    public:
        virtual value_t Next(std::default_random_engine& gen) override;
    
    private:
        std::uniform_real_distribution<value_t> dis;
    };

    // Normal
    class NormalDistribution : public Distribution
    {
    public:
        NormalDistribution(const value_t MEAN, const value_t STDDEV);

    public:
        virtual value_t Next(std::default_random_engine& gen) override;
    
    private:
        std::normal_distribution<value_t> dis;
    };

    class Initializer
    {
    public:
        static Initializer Uniform(const value_t a = -1, const value_t b = 1);
        static Initializer Normal(const value_t MEAN = 0, const value_t STDDEV = 1);

    public:
        // The global seed randomly
        // selected by default
        static uint_fast32_t Seed;

    public:
        Initializer(Distribution *dis);
        ~Initializer();

    public:
        virtual void Init(Tensor& data);

    private:
        Distribution *dis;
        std::default_random_engine generator;
    };
} // namespace im
