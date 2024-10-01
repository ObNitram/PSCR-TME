#pragma once
#include <cassert>
#include <cstddef>
#include <utility>

namespace pscr
{

template <typename T> class List
{
    struct Node
    {
        T data;
        Node *next;
    };

    Node *head = nullptr;
    Node *tail = nullptr;
    size_t _size = 0;

  public:
    List() = default;

    List(const List &other)
    {
        Node *other_itr = other.head;
        while (other_itr != nullptr)
        {
            push_back(other_itr->data);
            other_itr = other_itr->next;
        }
    }

    List(List &&other) noexcept : head(other.head), tail(other.tail), _size(other._size) { other.head = nullptr; }

    List &operator=(const List &other)
    {
        if (&other == this) return *this;

        while (head != nullptr)
        {
            Node *next = head->next;
            delete head;
            head = next;
        }
        tail = nullptr;

        Node *current = other.head;
        while (current != nullptr)
        {
            push_back(current->data);
            current = current->next;
        }

        return *this;
    }

    List &operator=(List &&other) noexcept
    {
        if (&other == this) return *this;

        std::swap(head, other.head);
        std::swap(tail, other.tail);
        std::swap(_size, other._size);

        return *this;
    }

    ~List()
    {
        while (head != nullptr)
        {
            Node *next = head->next;
            delete head;
            head = next;
        }
    }

    T &operator[](size_t index)
    {
        assert(index < _size);
        Node *current = head;
        for (size_t i = 0; i < index; i++)
        {
            current = current->next;
        }
        return current->data;
    }

    void push_back(const T &val)
    {
        Node *newNode = new Node{val, nullptr};
        if (head == nullptr)
        {
            assert(tail == nullptr);
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        _size++;
    }

    void push_front(const T &val)
    {
        Node *newNode = new Node{val, head};
        head = newNode;
        _size++;
    }

    [[nodiscard]] size_t size() const { return _size; }
    [[nodiscard]] bool isEmpty() const { return head == nullptr; }
};
} // namespace pscr
