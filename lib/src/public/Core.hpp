#pragma once
#include <cstddef>

namespace pscr
{
class Core
{
  public:
    static size_t strlen(const char *str);
    static char *newCopy(const char *str);

    template <typename T_iterator> static size_t count(T_iterator begin, T_iterator end)
    {
        size_t counter = 0;
        for (; begin != end; ++begin)
        {
            counter++;
        }
        return counter;
    }

    template <typename T_iterator, typename T>
    static size_t count_if_equal(T_iterator begin, T_iterator end, const T &val)
    {
        size_t counter = 0;
        for (; begin != end; ++begin)
        {
            if (*begin == val) counter++;
        }
        return counter;
    }
};
} // namespace pscr