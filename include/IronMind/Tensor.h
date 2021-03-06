#pragma once

// A tensor is a collection that gather
// multiple values and have a shape 

#include <vector>
#include <string>
#include "IronMind/Loss.h"
#include "IronMind/types.h"
#include "IronMind/Initializer.h"

namespace im
{
    class Tensor
    {
        friend value_t Loss::Compare(const Tensor&, const Tensor&) const;
        friend void Initializer::Init(Tensor&);

    public:
        // Loads a tensor using buffer or file
        static Tensor Load(const std::vector<uint8_t>& BUFFER);
        static Tensor Load(const std::string& PATH);

        // Creates tensor plenty of values
        static Tensor Values(const shape_t& SHAPE, const value_t VAL=0.f);

    public:
        Tensor();
        Tensor(const value_list_t& DATA, const shape_t& SHAPE);
        Tensor(const Tensor& OTHER);
        ~Tensor();

    public:
        // The number of values
        size_t Size() const;
        shape_t Shape() const;
        // A pointer to all values
        const value_t *Data() const;

        // Reshapes the tensor
        // The tensor must contain
        // the same values after this call
        void Reshape(const shape_t SHAPE);

        // String representation functions
        std::string ToString() const;
        void Print() const;

        // To save it
        std::vector<uint8_t> ToBytes() const;
        void Save(const std::string& PATH) const;

        // Computes the weigthed sum
        // Optimized version of vector dot weights
        // If TRANSPOSE, WEIGHTS will be transposed
        // * This tensor must have one dimension (a shape like { n })
        // * The second tensor must have two dimensions (a shape like { n, m })
        // * The result will have a shape like { m }
        Tensor WeightedSum(const Tensor &WEIGHTS, const bool TRANSPOSE=false) const;

        // Computes the outer product of two vectors (one dimensional tensors)
        // * They must have shapes { n } and { m }
        // * The result has the shape { n, m }
        Tensor Outer(const Tensor &OTHER) const;

        // Applies the function f on each values
        Tensor &Map(void (*f)(float &val));

        // Adds 1 to the shape DIMS times
        Tensor &ExpandDims(const size_t DIMS=1);

        // Set values to zero
        Tensor &Zero();

        // Set values to VALUE
        Tensor &Set(const value_t VAL);

    public:
        // Access to an item
        value_t operator[](const shape_t& INDICES) const;
        value_t &operator[](const shape_t& INDICES);
        Tensor &operator=(const Tensor& OTHER);

        // Element wise operations
        Tensor &operator+=(const Tensor& OTHER);
        Tensor &operator-=(const Tensor& OTHER);
        Tensor &operator*=(const Tensor& OTHER);
        Tensor &operator/=(const Tensor& OTHER);
        Tensor operator+(const Tensor& OTHER) const;
        Tensor operator-(const Tensor& OTHER) const;
        Tensor operator*(const Tensor& OTHER) const;
        Tensor operator/(const Tensor& OTHER) const;

        Tensor &operator*=(const value_t v);
        Tensor operator*(const value_t v) const;

    private:
        // Unsafe constructor
        // !!! DATA is not duplicated
        // !!! DATA, SHAPE, SIZE are not verified
        Tensor(value_t *data, const shape_t& SHAPE, const size_t SIZE);

    private:
        // Inits the shape and size
        // !!! Don't use this function after construction
        void initShape(const shape_t& SHAPE);

        // Returns the index of the value with indices
        size_t posAt(const shape_t& INDICES) const;

        // Reallocates and copies the data
        // !!! The old data is not freed
        void duplicateData();

    private:
        // The size is the product of each term of the shape
        // This is the number of values in data
        shape_t shape;
        size_t size;

        // Raw data
        value_t *data;
    };
} // namespace im
