#include "IronMind/Tensor.h"
#include <iostream>
#include <sstream>
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
