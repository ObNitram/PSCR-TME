#pragma once
#include <cassert>
#include <cstddef>

namespace pscr
{
template <typename T> class Vector
{
    size_t _size;
    size_t _capacity;
    T *_data;

  public:
    Vector(const size_t capacity = 10)
    {
        assert(capacity > 0);
        _size = 0;
        _capacity = capacity;
        _data = new T[capacity];
    }

    Vector(const Vector &other)
    {
        _size = other._size;
        _capacity = other._capacity;
        _data = new T[_capacity];
        for (size_t i = 0; i < _size; i++) { _data[i] = other._data[i]; }
    }
    Vector(Vector &&other) noexcept
    {
        _size = other._size;
        _capacity = other._capacity;
        _data = other._data;

        other._size = 0;
        other._capacity = 0;
        other._data = nullptr;
    }

    Vector &operator=(const Vector &other)
    {
        if (&other == this) { return *this; }

        if (_capacity < other._capacity)
        {
            delete[] _data;
            _data = new T[other._capacity];
        }

        _size = other._size;
        _capacity = other._capacity;
        _data = new T[other._capacity];
        for (size_t i = 0; i < _size; i++) { _data[i] = other._data[i]; }
        return *this;
    }

    Vector &operator=(Vector &&other) noexcept
    {
        if (&other == this) { return *this; }

        delete[] _data;

        _size = other._size;
        _capacity = other._capacity;
        _data = other._data;

        other._size = 0;
        other._capacity = 0;
        other._data = nullptr;

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

    void push_back(const T &val)
    {
        ensure_capacity();
        _data[_size++] = val;
    }

    size_t size() const { return _size; }

    bool isEmpty() const { return _size == 0; }

  private:
    void ensure_capacity()
    {
        if (_size < _capacity) { return; }

        _capacity = _capacity * 2;
        T *new_data = new T[_capacity];

        for (size_t i = 0; i < _size; i++) { new_data[i] = _data[i]; }

        delete[] _data;
        _data = new_data;
    }
};
} // namespace pscr
