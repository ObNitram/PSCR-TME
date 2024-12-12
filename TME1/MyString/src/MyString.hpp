//
// Created by obnitram on 20/09/24.
//

#pragma once
#include <ostream>

namespace pr
{
class MyString
{
    char *str;

public:
    MyString(const char *src);

    MyString(const MyString &other);

    MyString(MyString &&other) noexcept;

    MyString &operator=(const MyString &other);

    MyString &operator=(MyString &&other) noexcept;

    ~MyString();

    friend std::ostream &operator<<(std::ostream &os, const MyString &obj)
    {
        return os << (obj.str ? obj.str : "null");
    }
};
} // pr