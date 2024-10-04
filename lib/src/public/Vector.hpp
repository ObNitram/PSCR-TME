#pragma once
#include <cassert>
#include <cstddef>
#include <utility>

namespace pscr
{
template <typename T> class Vector
{
    static constexpr size_t default_size = 10;
    static constexpr size_t grow_factor = 2;

    size_t _size;
    size_t _capacity;
    T *_data;

  public:
    Vector(const size_t size = default_size)
    {
        assert(size > 0);
        _size = size;
        _capacity = size;
        _data = new T[size];
    }

    Vector(const Vector &other)
    {
        _size = other._size;
        _capacity = other._capacity;
        _data = new T[_capacity];
        for (size_t i = 0; i < _size; i++)
        {
            _data[i] = other._data[i];
        }
    }

    Vector(Vector &&other) noexcept
    {
        _size = other._size;
        _capacity = other._capacity;
        std::swap(_data, other._data);

        other._data = nullptr;
    }

    Vector &operator=(const Vector &other)
    {
        if (&other == this)
        {
            return *this;
        }

        if (_capacity < other._capacity)
        {
            delete[] _data;
            _data = new T[other._capacity];
            _capacity = other._capacity;
        }

        _size = other._size;
        for (size_t i = 0; i < _size; i++)
        {
            _data[i] = other._data[i];
        }
        return *this;
    }

    Vector &operator=(Vector &&other) noexcept
    {
        if (&other == this)
        {
            return *this;
        }

        std::swap(_data, other._data);
        std::swap(_size, other._size);
        std::swap(_capacity, other._capacity);

        return *this;
    }

    ~Vector() { delete[] _data; }

    T &operator[](size_t index)
    {
        assert(index < _size);
        return _data[index];
    }

    const T &operator[](size_t index) const
    {
        assert(index < _size);
        return _data[index];
    }

    typedef T *iterator;
    iterator begin() { return _data; }
    iterator end() { return _data + _size; }

    typedef T *const_iterator;
    const_iterator begin() const { return _data; }
    const_iterator end() const { return _data + _size; }

    void push_back(const T &val)
    {
        ensure_capacity();
        _data[_size++] = val;
    }

    [[nodiscard]] size_t size() const { return _size; }

    [[nodiscard]] bool isEmpty() const { return _size == 0; }

  private:
    void ensure_capacity()
    {
        if (_size < _capacity)
        {
            return;
        }

        _capacity = _capacity * grow_factor;
        T *new_data = new T[_capacity];

        for (size_t i = 0; i < _size; i++)
        {
            new_data[i] = std::move(_data[i]);
        }

        delete[] _data;
        _data = new_data;
    }
};
} // namespace pscr
