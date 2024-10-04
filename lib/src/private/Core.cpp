#include "Core.hpp"

#include <cstring>

namespace pscr
{
size_t Core::strlen(const char *str)
{
    for (const char *itr = str;; ++itr)
    {
        if (*itr == '\0')
        {
            return reinterpret_cast<size_t>(itr) - reinterpret_cast<size_t>(str);
        }
    }
}

char *Core::newCopy(const char *str)
{
    const size_t len = strlen(str) + 1;
    const auto copy = new char[len];
    memcpy(copy, str, len);
    return copy;
}
} // namespace pscr