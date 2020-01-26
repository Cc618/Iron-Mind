#include "IronMind/io.h"
#include <fstream>
#include <ios>
#include <iterator>

namespace im
{
    bool WriteFile(const std::string& PATH, const std::vector<uint8_t>& BYTES)
    {
        std::ofstream file(PATH, std::ios::out | std::ios::binary);

        if (file.is_open())
        {
            file.write((const char*)&BYTES[0], BYTES.size());

            file.close();

            return true;
        }

        return false;
    }

    std::vector<uint8_t> ReadFile(const std::string& PATH)
    {
        std::ifstream file(PATH, std::ios::in | std::ios::binary);

        if (file.is_open())
        {
            std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(file), {});

            file.close();

            return buffer;
        }

        return {};
    }
} // namespace im
