#pragma once
#include <cstddef>

namespace pscr
{
template <typename T> class Vector
{
  public:
    Vector(int size = 10);

    Vector(const Vector &other);
    Vector(Vector &&other) noexcept;

    Vector &operator=(const Vector &other);
    Vector &operator=(Vector &&other) noexcept;

    ~Vector();

    T &operator[](size_t index);
    const T &operator[](size_t index) const;

    void push_back(const T &val);
    size_t size() const;
    bool empty() const;
};
} // namespace pscr
