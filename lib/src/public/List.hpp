#pragma once
#include <cstddef>

namespace pscr
{

template <typename T> class List
{
  public:
    List();

    List(const List &other);
    List(const List &&other) noexcept;

    List &operator=(const List &other);
    List &operator=(List &&other) noexcept;

    ~List();

    T &operator[](size_t index);

    void push_back(const T &val);
    void push_front(const T &val);

    size_t size() const;
    bool isEmpty() const;
};
} // namespace pscr
