#pragma once

#include <condition_variable>
#include <cstring>
#include <mutex>

namespace pr
{

template <typename T> class Queue
{
    T **tab;
    const size_t _allocsize;
    size_t _begin;
    size_t _size;

    mutable std::mutex _mutex;
    mutable std::condition_variable _cond;
    mutable std::atomic<bool> _behavior_is_to_wait = true;

  public:
    explicit Queue(const size_t size) : _allocsize(size), _begin(0), _size(0)
    {
        tab = new T *[size];
        memset(tab, 0, size * sizeof(T *));
    }

    ~Queue()
    {
        // ?? lock a priori inutile, ne pas detruire si on travaille encore avec
        for (size_t i = 0; i < _size; i++)
        {
            auto ind = (_begin + i) % _allocsize;
            delete tab[ind];
        }
        delete[] tab;
    }

    size_t size() const
    {
        std::lock_guard lg(_mutex);
        return _size;
    }

    T *pop()
    {
        std::unique_lock lg(_mutex);
        while (empty())
        {
            if (!_behavior_is_to_wait) return nullptr;
            _cond.wait(lg);
        }
        auto ret = tab[_begin];
        tab[_begin] = nullptr;
        _size--;
        _begin = (_begin + 1) % _allocsize;
        _cond.notify_all();
        return ret;
    }

    bool push(T *elt)
    {
        std::unique_lock lg(_mutex);
        while (full())
        {
            if (!_behavior_is_to_wait) return false;
            _cond.wait(lg);
        }
        tab[(_begin + _size) % _allocsize] = elt;
        _size++;
        _cond.notify_all();
        return true;
    }

    void setBehavior(const bool behavior_is_to_wait)
    {
        std::lock_guard lg(_mutex);
        _behavior_is_to_wait = behavior_is_to_wait;
        _cond.notify_all();
    }

  private:
    // fonctions private, sans protection mutex
    bool empty() const { return _size == 0; }

    bool full() const { return _size == _allocsize; }
};

} // namespace pr
