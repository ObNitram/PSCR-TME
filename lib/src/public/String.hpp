#pragma once
#include <ostream>

namespace pscr
{

class String
{

    char *str;

  public:
    String(const char *src);

    String(const String &other);

    String(String &&other) noexcept;

    String &operator=(const String &other);

    String &operator=(String &&other) noexcept;

    ~String();

    friend std::ostream &operator<<(std::ostream &os, const String &obj);
};

} // namespace pscr
