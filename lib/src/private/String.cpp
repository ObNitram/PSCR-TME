#include "../public/String.hpp"

#include <cassert>
#include <cstring>

namespace pscr
{
String::String(const char *src)
{
    assert(src != nullptr);
    str = new char[strlen(src) + 1];
    strcpy(str, src);
}

String::String(const String &other)
{
    assert(other.str != nullptr);
    str = new char[strlen(other.str) + 1];
    strcpy(str, other.str);
}

String::String(String &&other) noexcept : str(other.str)
{
    assert(other.str != nullptr);
    other.str = nullptr;
}

String &String::operator=(const String &other)
{
    assert(other.str != nullptr);
    if (&other == this) return *this;

    delete[] str;
    str = new char[strlen(other.str) + 1];
    strcpy(str, other.str);

    return *this;
}

String &String::operator=(String &&other) noexcept
{
    assert(other.str != nullptr);
    if (&other == this) return *this;
    delete[] str;
    str = other.str;
    other.str = nullptr;
    return *this;
}
String::~String() { delete[] str; }

std::ostream &operator<<(std::ostream &os, const String &obj) { return os << (obj.str ? obj.str : "null"); }
} // namespace pscr