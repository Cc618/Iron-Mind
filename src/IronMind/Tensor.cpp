#include "IronMind/Tensor.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string.h>
#include "IronMind/errors.h"

namespace im
{
    Tensor::Tensor()
        : data(nullptr)
    {
        initShape({});
    }

    Tensor::Tensor(const value_list_t& DATA, const shape_t& SHAPE)
    {
        initShape(SHAPE);

        // Invalid shape
        Assert(size == DATA.size(), "(Tensor::Tensor) DATA has too many or too few items for SHAPE");

        // Allocate and copy the data from the list to the tensor
        data = new float[size];
        memcpy(data, &DATA[0], size * sizeof(value_t));
    }

    Tensor::Tensor(const Tensor& OTHER)
        : size(OTHER.size), shape(OTHER.shape), data(OTHER.data)
    {
        // Reallocates data
        duplicateData();
    }

    Tensor::~Tensor()
    {
        delete[] data;
    }

    size_t Tensor::Size() const
    {
        return size;
    }

    shape_t Tensor::Shape() const
    {
        return shape;
    }

    const value_t *Tensor::Data() const
    {
        return data;
    }

    void Tensor::Reshape(const shape_t SHAPE)
    {
        // Make the product
        size_t newSize = 1;
        for (const auto &val : SHAPE)
        {
            Assert(val != 0, "(Tensor::Reshape) Items in SHAPE must be non-null");
            newSize *= val;
        }

        Assert(newSize == size, "(Tensor::Reshape) Can't reshape, the number of values is not the same as before");

        // Update attributes
        shape = SHAPE;
        size = newSize;
    }

    std::string Tensor::ToString() const
    {
        // Separators for each dimension (the last one is used for all biggest dimensions)
        constexpr const char *SEPARATORS[] = {" ", "\n\t", "\n\n\t", "\n\n\n\t", "\n\n\t... ... ...\n\n\t"};

        // Empty
        if (size == 0)
            return "{}";

        std::stringstream ss;

        const size_t SHAPE_SIZE = shape.size();

        ss << "{\n\t";
        ss << data[0];

        for (int i = 1; i < size; ++i)
        {
            // The current dimension of the element
            size_t dim = 0;
            size_t ni = i;
            // Increase dim by how many end of dimension i is
            for (size_t d = SHAPE_SIZE - 1; d != 0 &&
                ni % shape[d] == 0 &&
                dim < sizeof(SEPARATORS) / sizeof(char*) - 1; --d)
            {
                ni /= shape[d];
                ++dim;
            }

            // Print item
            ss << ',' << SEPARATORS[dim] << data[i];
        }

        ss << "\n}";

        return ss.str();
    }

    void Tensor::Print() const
    {
        std::cout << ToString() << '\n';
    }

    Tensor Tensor::WeightedSum(const Tensor &WEIGHTS) const
    {
        Assert(shape.size() == 1, "(Tensor::WeightedSum) The first tensor must have one dimension");
        Assert(WEIGHTS.shape.size() == 2, "(Tensor::WeightedSum) The second tensor must have two dimensions");
        Assert(WEIGHTS.shape[0] == shape[0], "(Tensor::WeightedSum) The second tensor must have a shape "
            "like { n, m } and the first { n } but first.n != second.n");

        const size_t RESULT_SIZE = WEIGHTS.shape[1];
        Tensor result(new float[RESULT_SIZE], { RESULT_SIZE }, RESULT_SIZE);
       
        for (size_t i = 0; i < RESULT_SIZE; ++i)
        {
            // Init the sum to 0
            result.data[i] = 0;
            
            // Compute the weighted sum
            for (size_t j = 0; j < size; ++j)
                result.data[i] += data[j] * WEIGHTS.data[j * RESULT_SIZE + i];
        }

        return result;
    }
    
    Tensor &Tensor::Map(void (*f)(float &val))
    {
        for (size_t i = 0; i < size; ++i)
            f(data[i]);

        return *this;
    }

    Tensor &Tensor::ExpandDims(const size_t DIMS)
    {
        const size_t SIZE = shape.size();
        shape.resize(SIZE + DIMS);

        // Move values
        for (size_t i = SIZE - 1; i < SIZE; --i)
            shape[i + DIMS] = shape[i];

        // Add 1
        for (size_t i = 0; i < DIMS; ++i)
            shape[i] = 1;

        return *this;
    }

    value_t Tensor::operator[](const shape_t& INDICES) const
    {
        return data[posAt(INDICES)];
    }

    value_t &Tensor::operator[](const shape_t& INDICES)
    {
        return data[posAt(INDICES)];
    }

    Tensor &Tensor::operator=(const Tensor& OTHER)
    {
        // Free data
        delete[] data;

        // Change shape and size
        size = OTHER.size;
        shape = OTHER.shape;

        // Duplicate data
        data = OTHER.data;
        duplicateData();

        return *this;
    }

    Tensor &Tensor::operator+=(const Tensor& OTHER)
    {
        Assert(shape == OTHER.shape, "(Tensor::+=) The shapes must be equal");

        for (size_t i = 0; i < size; ++i)
            data[i] += OTHER.data[i];

        return *this;
    }

    Tensor &Tensor::operator-=(const Tensor& OTHER)
    {
        Assert(shape == OTHER.shape, "(Tensor::-=) The shapes must be equal");

        for (size_t i = 0; i < size; ++i)
            data[i] -= OTHER.data[i];

        return *this;
    }

    Tensor &Tensor::operator*=(const Tensor& OTHER)
    {
        Assert(shape == OTHER.shape, "(Tensor::*=) The shapes must be equal");

        for (size_t i = 0; i < size; ++i)
            data[i] *= OTHER.data[i];

        return *this;
    }

    Tensor &Tensor::operator/=(const Tensor& OTHER)
    {
        Assert(shape == OTHER.shape, "(Tensor::/=) The shapes must be equal");

        for (size_t i = 0; i < size; ++i)
            data[i] /= OTHER.data[i];

        return *this;
    }

    Tensor Tensor::operator+(const Tensor& OTHER) const
    {
        Assert(shape == OTHER.shape, "(Tensor::+) The shapes must be equal");

        Tensor result(new float[size], shape, size);

        for (size_t i = 0; i < result.size; ++i)
            result.data[i] = data[i] + OTHER.data[i];

        return result;
    }

    Tensor Tensor::operator-(const Tensor& OTHER) const
    {
        Assert(shape == OTHER.shape, "(Tensor::-) The shapes must be equal");

        Tensor result(new float[size], shape, size);

        for (size_t i = 0; i < result.size; ++i)
            result.data[i] = data[i] - OTHER.data[i];

        return result;
    }

    Tensor Tensor::operator*(const Tensor& OTHER) const
    {
        Assert(shape == OTHER.shape, "(Tensor::*) The shapes must be equal");

        Tensor result(new float[size], shape, size);

        for (size_t i = 0; i < result.size; ++i)
            result.data[i] = data[i] * OTHER.data[i];

        return result;
    }

    Tensor Tensor::operator/(const Tensor& OTHER) const
    {
        Assert(shape == OTHER.shape, "(Tensor::/) The shapes must be equal");

        Tensor result(new float[size], shape, size);

        for (size_t i = 0; i < result.size; ++i)
            result.data[i] = data[i] / OTHER.data[i];

        return result;
    }

    Tensor &Tensor::operator*=(const value_t v)
    {
        for (size_t i = 0; i < size; ++i)
            data[i] *= v;

        return *this;
    }

    Tensor Tensor::operator*(const value_t v) const
    {
        Tensor result(new float[size], shape, size);

        // auto Tensor 
        for (size_t i = 0; i < result.size; ++i)
            result.data[i] *= v;

        return result;
    }

    Tensor::Tensor(value_t *data, const shape_t& SHAPE, const size_t SIZE)
        : data(data), shape(SHAPE), size(SIZE)
    {}

    void Tensor::initShape(const shape_t& SHAPE)
    {
        shape = SHAPE;

        if (SHAPE.empty())
        {
            size = 0;
            return;
        }

        // Make the product
        size = 1;
        for (const auto &val : SHAPE)
        {
            Assert(val != 0, "(Tensor::initShape) Items in SHAPE must be non-null");
            size *= val;
        }
    }

    size_t Tensor::posAt(const shape_t& INDICES) const
    {
        const size_t INDICES_SIZE = INDICES.size();

        Assert(INDICES_SIZE == shape.size(), "(Tensor::[]) INDICES must have the same dimension as the tensor shape");
        Assert(!shape.empty(), "(Tensor::[]) The tensor doesn't contain values");

        size_t pos = 0;

        // The length of the sub tensor
        size_t offset = 1;

        // Iterate backwards (from smallest to biggest dimension)
        for (size_t i = INDICES_SIZE - 1; i < INDICES_SIZE; --i)
        {
            Assert(INDICES[i] < shape[i], "(Tensor::[]) Indices must be smaller than the shape");
            pos += INDICES[i] * offset;
            offset *= shape[i];
        }

        return pos;
    }

    void Tensor::duplicateData()
    {
        value_t *old = data;

        // Allocate
        data = new float[size];

        // Copy
        memcpy(data, old, size * sizeof(float));
    }
} // namespace im
