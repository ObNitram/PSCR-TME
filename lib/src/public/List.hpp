#pragma once
#include <utility>
#include <cassert>
#include <cstddef>

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
    size_t _size = 0;

  public:
    List() = default;

    List(const List &other)
    {
        Node *current = other.head;
        while (current != nullptr)
        {
            push_back(current->data);
            current = current->next;
        }
    }

    List(List &&other) noexcept : head(other.head), _size(other._size)
    {
        other.head = nullptr;
        other._size = 0;
    }

    List &operator=(const List &other)
    {
        if (&other == this) return *this;

        while (head != nullptr)
        {
            Node *next = head->next;
            delete head;
            head = next;
        }

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

        _size = other._size;
        std::swap(head, other.head);

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
        for (size_t i = 0; i < index; i++) { current = current->next; }
        return current->data;
    }

    void push_back(const T &val)
    {
        Node *newNode = new Node{val, nullptr};
        if (head == nullptr) { head = newNode; }
        else
        {
            Node *current = head;
            while (current->next != nullptr) { current = current->next; }
            current->next = newNode;
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
