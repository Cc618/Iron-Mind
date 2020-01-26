#pragma once

// A tensor is a collection that gather
// multiple values and have a shape 

#include <vector>
#include <string>
#include "IronMind/types.h"

namespace im
{
    class Tensor
    {
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

        // String representation functions
        std::string ToString() const;
        void Print() const;

    public:
        // Access to an item
        value_t operator[](const shape_t& INDICES) const;
        value_t &operator[](const shape_t& INDICES);
        Tensor &operator=(const Tensor& OTHER);

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
